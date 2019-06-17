import wave
import struct

from typing import Tuple

from arduino_midi import *

COIL_FREQ = 250e3  # 250 kHz coil frequency
CYCLE_LENGTH = 1.0 / COIL_FREQ
MAX_CYCLES = 10  # Maximum number of cycles in a pulse
MAX_PULSE_LENGTH = MAX_CYCLES * CYCLE_LENGTH
PULSE_DECAY_CYCLES = 5  # Number of cycles to runoff pulse
PULSE_DECAY = PULSE_DECAY_CYCLES * CYCLE_LENGTH

SAMPLE_RATE = 44100  # Hz
PULSE_INIT = 10000.0  # Initial 'attack' value of pulse
PULSE_STEP = 5000.0  # Additional volume per cycle
PULSE_SLOPE = PULSE_STEP / CYCLE_LENGTH
PULSE_MAX = 32767.0  # Maximum pulse volume (16-bit)

MIDI_BASE_FREQ = 440.0  # A note = 440 Hz
MIDI_BASE_NOTE = 69  # A4


def get_midi_freq(note: int) -> float:
    return MIDI_BASE_FREQ * (2.0 ** (float(note - MIDI_BASE_NOTE) / 12))


ARDUINO_FREQ = 16.0e6  # 16 MHz


class ArduinoTimerSim:
    def __init__(self, max: int, prescale_values: List[int]):
        self.max: int = max
        self.prescale_values: List[int] = prescale_values
        self.prescale: int = 1
        self.top: int = max
        self.duty: int = 0
        self.current: int = 0
        self.current_t: float = 0

    def set_note(self, note, volume):
        tgt_freq = get_midi_freq(note)
        self.prescale = next(v for v in self.prescale_values if
                             ARDUINO_FREQ / (self.max * v) < tgt_freq)
        self.top = int(round(ARDUINO_FREQ / (self.prescale * tgt_freq)))
        tgt_pulse = min(volume, MAX_CYCLES) * CYCLE_LENGTH
        self.duty = int(round(tgt_pulse * ARDUINO_FREQ / self.prescale))
        self.duty = 1 if self.duty == 0 else self.duty
        #print('MIDI note %3d, volume %2d > PRESCALE = %5d, TOP = %5d, DUTY = %5d' % (
        #    note, volume, self.prescale, self.top, self.duty))

    def set_off(self):
        self.duty = 0

    def current_state(self) -> bool:
        return self.current < self.duty

    def next_change(self) -> float:
        if self.current_state():
            return self.current_t + float(self.duty - self.current) * self.prescale / ARDUINO_FREQ
        else:
            return self.current_t + float(self.top - self.current) * self.prescale / ARDUINO_FREQ

    def update(self, t: float):
        ticks = int(round((t - self.current_t) * ARDUINO_FREQ / self.prescale))
        self.current += ticks
        self.current -= self.top * int(self.current / self.top)
        self.current_t = t


Timer1 = ArduinoTimerSim(1 << 16, [1, 8, 64, 256, 1024])
Timer2 = ArduinoTimerSim(1 << 8, [1, 8, 32, 64, 128, 256, 1024])
ArduinoTimers = [Timer1, Timer2]


def generate_logic_signal(mid: mido.MidiFile) -> List[Tuple[float, float]]:
    current_state = True
    current_pulse_start = 0.0
    pulses = list()

    current_t = 0.0
    current_tempo = 0

    def update_state(t):
        nonlocal current_t, current_pulse_start, current_state
        current_t = t
        Timer1.update(current_t)
        Timer2.update(current_t)
        new_state = Timer1.current_state() or Timer2.current_state()
        if new_state != current_state:
            if new_state:
                current_pulse_start = current_t
            else:
                pulse_end = min(current_pulse_start + MAX_PULSE_LENGTH, current_t)
                pulses.append((current_pulse_start, pulse_end))
            current_state = new_state

    last_cmd_t = 0.0
    cmds = get_midi_commands(mid)
    for cmd in cmds:
        cmd_t = last_cmd_t + float(cmd.time * current_tempo) / (1e6 * mid.ticks_per_beat)
        last_cmd_t = cmd_t
        while current_t < cmd_t:
            next_timer_change = min(Timer1.next_change(), Timer2.next_change())
            if next_timer_change < cmd_t:
                update_state(next_timer_change)
            else:
                update_state(cmd_t)
        if cmd.type == 'set_tempo':
            current_tempo = cmd.tempo
        elif cmd.type == 'note_off':
            ArduinoTimers[cmd.timer - 1].set_off()
        elif cmd.type == 'both_off':
            Timer1.set_off()
            Timer2.set_off()
        elif cmd.type == 'note_on':
            ArduinoTimers[cmd.timer - 1].set_note(cmd.note, cmd.volume)
        update_state(cmd_t)

    return pulses


def generate_wav(mid: mido.MidiFile, path: str):
    wav = wave.open(path, 'w')
    wav.setnchannels(1)  # mono
    wav.setsampwidth(2)  # 2 bytes per frame
    wav.setframerate(SAMPLE_RATE)

    # Generate a list of (start, stop) tuples for the interrupter logic signal
    logic_pulses = generate_logic_signal(mid)
    print('Found %d pulses - up to t = %5.2f' % (len(logic_pulses), logic_pulses[-1][-1]))

    # Generate volumes from pulses
    sample_t = -1.0
    last_t = logic_pulses[-1][-1] + PULSE_DECAY
    pulse_idx = 0
    while sample_t <= last_t:
        volume = 0.0
        while pulse_idx + 1 < len(logic_pulses) \
                and logic_pulses[pulse_idx][1] < sample_t:
            pulse_idx += 1
        curr_pulse_start = logic_pulses[pulse_idx][0]
        if curr_pulse_start > sample_t:
            if pulse_idx > 0:
                # If the current pulse is not active, check for decay from a previous pulse
                last_pulse = logic_pulses[pulse_idx - 1]
                if last_pulse[1] + PULSE_DECAY > sample_t:
                    last_pulse_length = last_pulse[1] - last_pulse[0]
                    last_pulse_max = min(PULSE_MAX, PULSE_INIT + PULSE_SLOPE * last_pulse_length)
                    volume = last_pulse_max * (1.0 - (sample_t - last_pulse[1]) / PULSE_DECAY)
        else:
            volume = min(PULSE_MAX, PULSE_INIT + PULSE_SLOPE * (sample_t - curr_pulse_start))
        wav.writeframesraw(struct.pack('<h', int(volume)))
        sample_t += 1.0 / SAMPLE_RATE
        # print(sample_t)
    wav.close()
