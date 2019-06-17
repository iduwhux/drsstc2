#pragma once

#include <arduino.h>

void setup_timers();

void play_midi_note(uint8_t note, uint8_t volume = 1, bool timer1 = true);
void silence_midi(bool timer1 = true);
void set_pwm_off();

void start_midi(byte* midi_pointer);
bool play_midi();   // Returns false when song is over
void pause_midi();
void resume_midi();

extern const byte MARRIAGE_OF_FIGARO[] PROGMEM;
extern const byte BACH_INVENTION[] PROGMEM;
extern const byte ODE_TO_JOY[] PROGMEM;
extern const byte WILLIAM_TELL[] PROGMEM;
extern const byte SUGAR_PLUM_FAIRY[] PROGMEM;
void load_next_song();


void send_single_pulse(unsigned long us);
