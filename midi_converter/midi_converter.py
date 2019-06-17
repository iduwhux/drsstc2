import argparse
import mido

from tesla_wav_simulator import generate_wav
from arduino_midi import *

from copy import deepcopy
from typing import List, Set
from os import path

NOTE_SEQ = ['A', 'A#', 'B', 'C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#']


def midi_note_name(note):
    note_letter = NOTE_SEQ[(note - 21) % 12]
    octave_number = int((note - 12) / 12)
    return '%s%d' % (note_letter, octave_number)


def assemble_midi_states(mid: mido.MidiFile, channel_lock: bool):
    state_array: List[MIDIState] = []
    state: MIDIState = MIDIState(0, set(), 0)

    trk_indexes = [0] * len(mid.tracks)
    trk_offset_times = [0] * len(mid.tracks)
    if channel_lock:
        channel_notes = dict()
    while True:
        prev_state: MIDIState = deepcopy(state)
        # First, consume all messages up to the current time
        for i, trk in enumerate(mid.tracks):
            cmd_cnt = 0
            while trk_indexes[i] < len(trk):
                msg = trk[trk_indexes[i]]
                if msg.time + trk_offset_times[i] <= state.time:
                    trk_offset_times[i] += msg.time
                    trk_indexes[i] += 1
                    if msg.type == 'set_tempo':
                        cmd_cnt += 1
                        state = MIDIState(state.time, state.notes, msg.tempo)
                    elif msg.type == 'note_off' or (msg.type == 'note_on' and msg.velocity == 0):
                        cmd_cnt += 1
                        state = MIDIState(state.time, set(filter(lambda n: n.note != msg.note, state.notes)),
                                          state.tempo)
                    elif msg.type == 'note_on':
                        cmd_cnt += 1
                        new_notes: Set[MIDINote] = state.notes.copy()
                        note_on_note = MIDINote(msg.note, msg.velocity)
                        if channel_lock:
                            channel = msg.channel
                            if channel in channel_notes and channel_notes[channel] in new_notes:
                                new_notes.remove(channel_notes[channel])
                            channel_notes[channel] = note_on_note
                        new_notes.add(note_on_note)
                        state = MIDIState(state.time, new_notes, state.tempo)
                else:
                    break
            # if cmd_cnt > 0:
            # print('Executed %d commands at time %d for track %d' % (cmd_cnt, state.time, i))
        if prev_state != state:
            # print(state)
            # print('Logging state %s at time %d' % (state, state.time))
            state_array.append(state)

        # Locate next command to execute
        next_time = 0
        for i, trk in enumerate(mid.tracks):
            if trk_indexes[i] < len(trk):
                next_msg_time = trk[trk_indexes[i]].time - (state.time - trk_offset_times[i])
                if next_time == 0 or next_msg_time < next_time: next_time = next_msg_time
        if next_time == 0:
            break
        state = MIDIState(state.time + next_time, state.notes, state.tempo)

    for i, s in enumerate(state_array):
        sorted_notes = list(reversed(sorted(s.notes, key=lambda n: n.note)))
        for j in range(len(sorted_notes)):
            for k in range(j + 1, len(sorted_notes)):
                if (sorted_notes[j].note - sorted_notes[k].note) % 12 == 0:
                    sorted_notes.append(sorted_notes.pop(k))

        state_array[i] = MIDIState(s.time, sorted_notes, s.tempo)
    return state_array


def get_simple_midi(ticks_per_beat, state_array: List[MIDIState],
                    tempo_factor: float, program=None):
    mid = mido.MidiFile(type=0, ticks_per_beat=ticks_per_beat)
    trk = mido.MidiTrack()
    mid.tracks.append(trk)
    trk.append(mido.Message('program_change', time=0, channel=0, program=program or 0))

    current_tempo = int(state_array[0].tempo / tempo_factor)

    time_diff = 0
    track_time = 0

    def write_msg(name, **kwargs):
        nonlocal track_time, time_diff
        tmp_params = dict(time=time_diff, **kwargs)
        trk.append(mido.Message(name, time=time_diff, **kwargs))
        track_time += time_diff
        time_diff = 0
        return '%s{%s}' % (name, ', '.join('%s=%s' % (k, v) for k, v in tmp_params.items()))

    def set_tempo_msg():
        nonlocal track_time, time_diff
        tmp_time_diff = time_diff
        trk.append(mido.MetaMessage('set_tempo', tempo=current_tempo))
        track_time += time_diff
        time_diff = 0
        return 'set_tempo{time=%d, tempo=%d}' % (tmp_time_diff, current_tempo)

    def print_time_msg(ticks, msg):
        beat = float(ticks) / input_midi.ticks_per_beat
        bar = int(beat / 4)
        beat = beat - bar * 4
        print('%3d   %4.2f   %s' % (bar, beat, msg))

    print_time_msg(0, '  START > ' + set_tempo_msg())
    for i, s in enumerate(state_array):
        if len(s.notes) > 0:
            note_str = ' '.join('%3s' % midi_note_name(n.note) for n in s.notes)
        else:
            note_str = '--'
        msgs = list()

        if i == 0:
            prev_state = MIDIState(time=0, notes=set(), tempo=state_array[0].tempo)
        else:
            prev_state = state_array[i - 1]
        time_diff = s.time - prev_state.time

        if s.tempo != prev_state.tempo:
            current_tempo = int(s.tempo / tempo_factor)
            msgs.append(set_tempo_msg())

        for n in prev_state.notes:
            if n not in s.notes:
                msgs.append(write_msg('note_off', note=n.note, velocity=n.volume, channel=0))

        for n in s.notes:
            if n not in prev_state.notes:
                msgs.append(write_msg('note_on', note=n.note, velocity=n.volume, channel=0))
        print_time_msg(s.time, '%7s > %s' % (note_str, ', '.join(msgs)))

    return mid


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Convert a MIDI file to C++',
                                     add_help=True)
    parser.add_argument('-i', '--input', metavar='PATH', type=str, nargs='?',
                        required=True, help='Input MIDI file')
    parser.add_argument('-o', '--output', metavar='PATH', type=str, nargs='?',
                        required=False, help='Output C++ file')
    parser.add_argument('-n', '--name', metavar='NAME', type=str, nargs='?',
                        required=True, help='Song name')
    parser.add_argument('--play', action='store_true',
                        help='Play final MIDI output')
    parser.add_argument('--wav', action='store_true',
                        help='Generate simulated WAV output')
    parser.add_argument('--channel_lock', action='store_true',
                        help='Assume note_off for subsequent note_on messages on the same channel')
    parser.add_argument('--midi_port', metavar='PORT', type=str,
                        nargs='?', required=False,
                        default=mido.get_output_names()[0],
                        help='Name of output MIDI port')
    parser.add_argument('--midi_program', metavar='N', type=int,
                        nargs='?', required=False,
                        help='MIDI program number (i.e. instrument)')
    parser.add_argument('--tempo_factor', metavar='F', type=float,
                        nargs='?', required=False, default=1.0,
                        help='Scale factor to speed up/down')
    parser.add_argument('--vol_scale', metavar='N', type=float,
                        nargs='?', required=False, default=10.0,
                        help='Scale factor for volume (lower=more amplification)')
    args = parser.parse_args()

    print('Reading MIDI file %s ...' % args.input)
    input_midi = mido.MidiFile(args.input)
    print('%d tracks found:\n' % len(input_midi.tracks) +
          '\n'.join('   %3d) %25s : %5d messages' % (i, trk.name, len(trk))
                    for i, trk in enumerate(input_midi.tracks)))
    print('%d ticks per beat' % input_midi.ticks_per_beat)

    state_array = assemble_midi_states(input_midi, channel_lock=args.channel_lock)
    total_notes = sum(len(s.notes) for s in state_array)
    print('Found %d states with %d notes over %d total ticks' %
          (len(state_array), total_notes, state_array[-1].time))
    print('\n'.join('%s' % str(s) for s in state_array))

    state_array = list(map(
        lambda s: MIDIState(s.time, s.notes[:2], s.tempo), state_array))
    rem_notes = sum(len(s.notes) for s in state_array)
    print('Removed %d lower notes' % (total_notes - rem_notes))

    mid = get_simple_midi(input_midi.ticks_per_beat, state_array, args.tempo_factor)
    input_mod_path = path.splitext(args.input)[0] + '_output.mid'
    print('Saving modified MIDI data to %s' % input_mod_path)
    mid.save(input_mod_path)

    cmds = get_midi_commands(mid, args.vol_scale)
    total_bytes = sum(map(lambda cmd: len(cmd.cmd_bytes), cmds))
    print('%d bytes total' % total_bytes)

    output_path = args.output or path.splitext(args.input)[0] + '.cpp'
    with open(output_path, 'w') as outf:
        outf.write('#include "MIDIPlayer.h"\n\n' +
                   '// converted from %s - %d bytes total\n' % (args.input, total_bytes) +
                   'extern const byte %s[] PROGMEM = \n{\n' % args.name +
                   '\n'.join(map(str, cmds)) +
                   '\n};\n')

    if args.wav:
        wav_path = path.splitext(args.input)[0] + '_tesla.wav'
        print('Generating simulated WAV file at %s' % wav_path)
        generate_wav(mid, args.vol_scale, wav_path)

    if args.play:
        print('Opening MIDI port %s' % args.midi_port)
        output_port = mido.open_output(args.midi_port)
        for msg in mid.play():
            output_port.send(msg)
