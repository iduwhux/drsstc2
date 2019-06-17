import mido

from collections import namedtuple
from typing import List

MIDINote = namedtuple('MIDINote', ['note', 'volume'])
MIDIState = namedtuple('MIDIState', ['time', 'notes', 'tempo'])


def byte_enc(byte):
    return '{0:#04x}'.format(byte)


def get_byte_str(bytes):
    return ','.join(map(byte_enc, bytes))


def varint_encode(value):
    bytes = [value & 0x7f]
    while (value > 0):
        value = value >> 7
        if (value > 0):
            bytes.append(value & 0x7f)
    bytes.reverse()
    bytes[-1] = bytes[-1] + 0x80
    return bytes


class MIDICommand:
    def __init__(self, time: int, type: str, **kwargs):
        self.time = time
        self.type = type
        self.cmd_bytes = varint_encode(time)
        if type == 'note_on':
            self.timer = kwargs.get('timer', 1)
            self.note = kwargs['note']
            self.volume = kwargs['volume']
            self.cmd_bytes.append((0x80 if self.timer == 1 else 0) + self.note)
            self.cmd_bytes.append(self.volume)
            self.cmd_str = 'T%d ON, NOTE %3d VOLUME %2d' % (self.timer, self.note, self.volume)
        elif type == 'note_off':
            self.timer = kwargs.get('timer', 1)
            self.cmd_bytes.append(0x80 if self.timer == 1 else 0x00)
            self.cmd_str = 'T%d OFF' % (self.timer)
        elif type == 'both_off':
            self.cmd_bytes.append(0x01)
            self.cmd_str = 'BOTH OFF'
        elif type == 'set_tempo':
            self.tempo = kwargs['tempo']
            self.cmd_bytes.append(0x02)
            self.cmd_bytes += varint_encode(self.tempo)
            self.cmd_str = 'TEMPO > %d' % self.tempo
        elif type == 'end_program':
            self.cmd_bytes.append(0x05)
            self.cmd_str = 'END PROGRAM'
        else:
            print('UNKNOWN COMMAND TYPE')

    def __str__(self):
        if self.type == 'end_program':
            fmt_str = '%30s  // %6d %s'
        else:
            fmt_str = '%30s, // %6d %s'
        return fmt_str % (get_byte_str(self.cmd_bytes), self.time, self.cmd_str)


def encode_midi_note_on(time, note, volume, timer1):
    bytes = varint_encode(time)
    bytes.append((0x80 if timer1 else 0) + note)
    bytes.append(volume)
    return '%30s, //%6d %s ON, NOTE %d VOLUME %d' % (
        get_byte_str(bytes), time, 'T1' if timer1 else 'T2', note, volume)


def encode_midi_note_off(time, timer1):
    bytes = varint_encode(time)
    bytes.append(0x80 if timer1 else 0x00)
    return '%30s, //%6d %s OFF' % (
        get_byte_str(bytes), time, 'T1' if timer1 else 'T2')


def encode_midi_both_off(time):
    bytes = varint_encode(time)
    bytes.append(0x01)
    return '%30s, //%6d BOTH OFF' % (
        get_byte_str(bytes), time)


def encode_midi_change_tempo(time, tempo):
    bytes = varint_encode(time)
    bytes.append(0x02)
    bytes += varint_encode(tempo)
    return '%30s, //%6d TEMPO > %d' % (
        get_byte_str(bytes), time, tempo)


def encode_midi_end_program(time):
    bytes = varint_encode(time)
    bytes.append(0x04)
    return '%30s  //%6d END OF FILE' % (
        get_byte_str(bytes), time)


def get_midi_commands(mid: mido.MidiFile) -> List[MIDICommand]:
    cmds = list()
    timer_notes = [None] * 2
    i = 0
    mark = 0
    while i < len(mid.tracks[0]):
        msg = mid.tracks[0][i]
        mark += msg.time

        def mark_cmd(name, **kwargs):
            nonlocal mark
            cmd = MIDICommand(mark, name, **kwargs)
            cmds.append(cmd)
            mark = 0

        if msg.type == 'set_tempo':
            # Simply consume change tempo messages
            mark_cmd('set_tempo', tempo=msg.tempo)
        else:
            new_timer_notes = timer_notes.copy()
            if msg.type == 'note_off':
                # Advance to consume additional note_off messages
                if i + 1 < len(mid.tracks[0]) and \
                        mid.tracks[0][i + 1].type == 'note_off' and \
                        mid.tracks[0][i + 1].time == 0:
                    i += 1
                    new_timer_notes = [None] * 2
                else:
                    timer_idx = next(t for t in range(2) if timer_notes[t] and timer_notes[t].note == msg.note)
                    new_timer_notes[timer_idx] = None

                # Advance to consume any note_on messages
                if i + 1 < len(mid.tracks[0]) and mid.tracks[0][i + 1].time == 0:
                    i += 1
                    msg = mid.tracks[0][i]
            if msg.type == 'note_on':
                # Find destination index; prefer timer1
                dest_idx = new_timer_notes.index(None) if None in new_timer_notes else 0
                new_timer_notes[dest_idx] = MIDINote(msg.note, int(msg.velocity / 10))
                # Advance to consume remaining note_on messages
                if i + 1 < len(mid.tracks[0]) and \
                        mid.tracks[0][i + 1].time == 0 and \
                        mid.tracks[0][i + 1].type == 'note_on':
                    i += 1
                    msg = mid.tracks[0][i]
                    new_timer_notes[1 - dest_idx] = MIDINote(msg.note, int(msg.velocity / 10))

            # Calculate messages
            if new_timer_notes == [None] * 2 and len([n for n in timer_notes if n]) > 0:
                mark_cmd('both_off')
            else:
                for t in range(2):
                    if new_timer_notes[t]:
                        if not timer_notes[t] or timer_notes[t] != new_timer_notes[t]:
                            n = new_timer_notes[t]
                            mark_cmd('note_on', note=n.note, volume=n.volume, timer=t + 1)
                    else:
                        if timer_notes[t]:
                            mark_cmd('note_off', timer=t + 1)
            timer_notes = new_timer_notes
        i += 1
    cmds.append(MIDICommand(0, 'end_program'))
    return cmds


def encode_simple_midi(mid: mido.MidiFile):
    return list(map(str, get_midi_commands(mid)))
