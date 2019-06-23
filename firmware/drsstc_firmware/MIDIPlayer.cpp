#include "StateMachine.h" // SERIAL_LOGGING flag
#include "MIDIPlayer.h"
#include "pin_definitions.h"
#include "LEDRing.h"

const uint16_t PRESCALE1_VALUES[] = {1, 8, 64, 256, 1024};
const uint16_t PRESCALE2_VALUES[] = {1, 8, 32, 64, 128, 256, 1024};

namespace {
  #define TIMER1_MIDI_OFFSET 21
  // Lookup table in Flash memory for 107 MIDI notes
  const uint16_t timer1_frequencies[] PROGMEM = 
    {9090,8580,64792,                                                            // octave 0
     61155,57723,54483,51425,48539,45814,43243,40816,38525,36363,34322,32395,
     30577,28861,27241,25712,24269,22907,21621,20407,19262,18181,17160,16197,
     15288,14430,13620,12855,12134,11453,10810,10203,9630,9090,8580,64792,
     61155,57723,54483,51425,48539,45814,43243,40816,38525,36363,34322,32395,
     30577,28861,27241,25712,24269,22907,21621,20407,19262,18181,17160,16197,
     15288,14430,13620,12855,12134,11453,10810,10203,9630,9090,8580,8098,
     7644,7214,6809,6427,6066,5726,5404,5101,4815,4544,4289,4049,
     3821,3607,3404,3213,3033,2862,2702,2550,2407,2272,2144,2024,
     1910,1803,1702,1606,1516,1431,1350,1275};                                   // octave 9
     
  uint8_t timer1_prescale_cs_bits(uint8_t midi_note) {
    if (midi_note <= 22) {
      return 3;
    } else if (midi_note <= 58) {
      return 2;
    } else {
      return 1;
    }
  }

  #define TIMER2_MIDI_OFFSET 35
  const uint8_t timer2_frequencies[] PROGMEM = 
    {252,                                               // octave 1
     238,224,212,200,189,178,168,158,149,141,133,126,
     118,112,105,99,94,88,83,79,74,70,66,252,
     238,224,212,200,189,178,168,158,149,141,133,252,
     238,224,212,200,189,178,168,158,149,141,133,252,
     238,224,212,200,189,178,168,158,149,141,133,252,
     238,224,212,200,189,178,168,158,149,141,133,126,
     118,112,105,99,94,88,83,79,74,70,66,252,
     238,224,212,200,189,178,168,158};                 // octave 9

  uint8_t timer2_prescale_cs_bits(uint8_t midi_note) {
    if (midi_note <= 58) {
      return 7;
    } else if (midi_note <= 70) {
      return 6;
    } else if (midi_note <= 82) {
      return 5;
    } else if (midi_note <= 94) {
      return 4;
    } else if (midi_note <= 118) {
      return 3;
    } else {
      return 2;
    }
  }

  const byte* read_varint(const byte* pointer, unsigned long& value) {
    if (!pointer) return nullptr;
    byte byte_value = *(pointer++);
    value = byte_value & 0x7f;
    while (!(byte_value & 0x80)) {
      byte_value = *(pointer++);
      value = (value << 7) + (unsigned long)(byte_value & 0x7f);
    }
    return pointer;
  }

  unsigned long peek_midi_time(const byte* pointer) {
    unsigned long midi_time = 0;
    read_varint(pointer, midi_time);
    return midi_time;
  }

  unsigned long current_tempo = 500000;        // us per beat (500000 = 120 bpm)
  unsigned long current_ticks_per_beat = 1024; // resolution

  #ifdef METRONOME
    // Metronome output to serial
    unsigned long metronome_mark_us = 0;
    unsigned long metronome_ticks = 0;
    unsigned long metronome_beat = 0;
  
    void reset_metronome(unsigned long timestamp) {
      metronome_mark_us = timestamp;
      metronome_ticks = 0;
      metronome_beat = 0;
      init_led_metronome();
      led_metronome_beat(0);
    }
  
    void update_metronome(unsigned long timestamp, bool force_mark) {
      if (metronome_mark_us == 0 || metronome_mark_us > timestamp)
        metronome_mark_us = timestamp;
  
      unsigned long new_ticks = metronome_ticks + ((timestamp - metronome_mark_us) * current_ticks_per_beat) / current_tempo;
      if (force_mark || new_ticks > current_ticks_per_beat) {
        metronome_ticks = new_ticks;
        while (metronome_ticks > current_ticks_per_beat) {
          metronome_ticks -= current_ticks_per_beat;
          #ifdef SERIAL_LOGGING
            Serial.print((metronome_beat >> 2) + 1);
            Serial.print(":");
            Serial.println((metronome_beat & 0x03) + 1);
          #endif
          metronome_beat++;
          led_metronome_beat(metronome_beat);
        }
      }
    }
  
    void pause_metronome(unsigned long timestamp) {
      update_metronome(timestamp, true);
      metronome_mark_us = 0;
    }
  
    void resume_metronome(unsigned long timestamp) {
      metronome_mark_us = timestamp;
      update_metronome(timestamp, false);
    }
  #endif
  
  const byte* play_midi_pointer(const byte* pointer, unsigned long timestamp) {
    if (!pointer) return nullptr;
    unsigned long beats = 0;
    pointer = read_varint(pointer, beats);
    byte note = *(pointer++);
    bool timer1 = (note & 0x80);
    note &= 0x7f;
    if (note == 0) {
      silence_midi(timer1);      
    } else if (note == 1) {   // Silence both
      set_pwm_off();
    } else if (note == 2) {   // Change tempo
      #ifdef METRONOME
      update_metronome(timestamp, true);
      #endif
      pointer = read_varint(pointer, current_tempo);
    } else if (note == 5) {   // End of file
      pointer = nullptr;
    } else {
      byte volume = *(pointer++);
      play_midi_note(note, volume, timer1);
    }
    return pointer;
  }

  inline void set_timer1_prescale(uint8_t CS_bits = 1) {
    CS_bits = (CS_bits == 0) ? 1 : (CS_bits > 5 ? 5 : CS_bits);
    
    // WGM13 + WGM12 (0x18) = fast PWM mode, ICR1 as TOP
    TCCR1B = _BV(WGM13) | _BV(WGM12) | CS_bits;
  }
  
  // Default value = 128x
  inline void set_timer2_prescale(uint8_t CS_bits = 5) {
    CS_bits = (CS_bits == 0) ? 1 : (CS_bits > 7 ? 7 : CS_bits);
    
    // WGM22 (0x08) = fast PWM mode, OCR2A as TOP
    TCCR2B = _BV(WGM22) | CS_bits;
  }
} // namespace

void setup_timers() {
  // Initialize PWM_1 timer
  // WGM11  (0x02) = fast PWM mode, ICR1 as TOP
  TCCR1A = _BV(WGM11);
  // Sets TCCR1B register
  set_timer1_prescale();
  OCR1A = 0;
  ICR1 = 65535; // Lowest frequency at 1x prescale = 244 Hz

  // Initialize PWM_2 timer
  // WGM21 + WGM20 (0x03) = fast PWM mode, OCR2A as TOP
  TCCR2A = _BV(WGM21) | _BV(WGM20);
  // Sets TCCR2B register
  set_timer2_prescale();
  OCR2B = 0;
  OCR2A = 255; // Lowest frequency at 128x prescale = 488 Hz
}

void silence_midi(bool timer1) {
  if (timer1) {
    TCCR1A = _BV(WGM11);
  } else {
    TCCR2A = _BV(WGM21) | _BV(WGM20);
  }
}

void set_pwm_off() {
  silence_midi(true);
  silence_midi(false);
}

// Number of 16MHz clock cycles in one 250 kHz cycle (16e6/250e3 = 64)
#define COIL_FREQ_CYCLES 64
#define COIL_FREQ_CYCLES_HALF 32
#define MAX_VOLUME 10

// Volume is interpreted as a number of cycles
void play_midi_note(uint8_t note, uint8_t volume, bool timer1) {
  if (note & 0x80) return;
  if (timer1) {
    if (note < TIMER1_MIDI_OFFSET) return;
    uint8_t cs_bits = timer1_prescale_cs_bits(note);
    uint16_t prescale_value = PRESCALE1_VALUES[cs_bits - 1];
    // Logic on the board forces switching on the full cycle only; so a volume level of 1 targets a 0.5 cycle ON time
    uint16_t tgt_duty = (min(volume, MAX_VOLUME) * COIL_FREQ_CYCLES_HALF) / prescale_value;
    tgt_duty = (tgt_duty > 0) ? tgt_duty - 1 : 0;
    uint16_t freq = timer1_frequencies[note - TIMER1_MIDI_OFFSET];
    set_timer1_prescale(cs_bits);
    
    OCR1A = tgt_duty >= freq ? freq - 1 : (uint8_t)tgt_duty;
    ICR1 = freq;

    // Initialize PWM_1 timer
    // COM1A1 (0x80) = non-inverted PWM output to timer 1 channel A (pin 9)
    // WGM11  (0x02) = fast PWM mode, ICR1 as TOP
    TCCR1A = _BV(COM1A1) | _BV(WGM11);
  } else {
    if (note < TIMER2_MIDI_OFFSET) return;    
    uint8_t cs_bits = timer2_prescale_cs_bits(note);
    uint16_t prescale_value = PRESCALE2_VALUES[cs_bits - 1];
    uint16_t tgt_duty = (min(volume, MAX_VOLUME) * COIL_FREQ_CYCLES_HALF) / prescale_value;
    tgt_duty = (tgt_duty > 0) ? tgt_duty - 1 : 0;
    uint8_t freq = timer2_frequencies[note - TIMER2_MIDI_OFFSET];
    set_timer2_prescale(cs_bits);
    
    OCR2B = tgt_duty >= freq ? freq - 1 : (uint8_t)tgt_duty;
    OCR2A = freq;

    // Initialize PWM_2 timer
    // COM2B1 (0x20) = non-inverted PWM output to timer 2 channel B (pin 3)
    // WGM21 + WGM20 (0x03) = fast PWM mode, OCR2A as TOP
    TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  }
}

namespace {
  const byte* current_midi_pointer = nullptr;

  bool is_paused = false;
  unsigned long prev_mark_us = 0;
}

bool play_midi() {
  if (is_paused || !current_midi_pointer) return false;
  unsigned long timestamp = micros();
  
  // catch micros wraparound
  if (prev_mark_us == 0 || prev_mark_us > timestamp) 
    prev_mark_us = timestamp;
    
  unsigned long next_ticks = peek_midi_time(current_midi_pointer);
  unsigned long rem_us = next_ticks * current_tempo / current_ticks_per_beat;
  while (timestamp >= prev_mark_us + rem_us) {
    prev_mark_us += rem_us;
    current_midi_pointer = play_midi_pointer(current_midi_pointer, timestamp);
    
    if (current_midi_pointer) {
      next_ticks = peek_midi_time(current_midi_pointer);
      rem_us = next_ticks * current_tempo / current_ticks_per_beat;      
    } else {
      prev_mark_us = 0;
      #ifdef SERIAL_LOGGING
        Serial.println(F("End of song"));
      #endif
      return false;
    }
  }
  
  #ifdef METRONOME
    update_metronome(timestamp, false);
  #endif

  return true;
}

void pause_midi() {
  is_paused = true;
  #ifdef METRONOME
  pause_metronome(micros());
  #endif
}

void resume_midi() {
  is_paused = false;
  prev_mark_us = micros();
  #ifdef METRONOME
  resume_metronome(prev_mark_us);
  #endif
}

void start_midi(const byte* midi_pointer) {
  current_midi_pointer = midi_pointer;
  current_midi_pointer = read_varint(current_midi_pointer, current_ticks_per_beat);
  current_midi_pointer = read_varint(current_midi_pointer, current_tempo);
  prev_mark_us = micros();
  #ifdef METRONOME
  reset_metronome(prev_mark_us);
  #endif
}

namespace {
  #define NUM_SONGS 5
  const byte* songs[] = {MARRIAGE_OF_FIGARO, SUGAR_PLUM_FAIRY, WILLIAM_TELL, ODE_TO_JOY, BACH_INVENTION};
  int prev_song_index = -1;

  #ifdef SERIAL_LOGGING
  const String song_names[] PROGMEM = {"Marriage of Figaro", "Dance of the Sugar Plum Fairy", "William Tell Overture", "Ode to Joy", "Bach Invention #1"};
  #endif
}

void load_next_song() { 
  int song_index = random(NUM_SONGS);
  while (song_index == prev_song_index) 
    song_index = random(NUM_SONGS);  
  start_midi(songs[song_index]);
  prev_song_index = song_index;
  #ifdef SERIAL_LOGGING
  Serial.print(F("Playing song: "));
  Serial.println(song_names[song_index]);
  #endif
}

void send_single_pulse(unsigned long us) {
    // Set timer 1 pin manual
    TCCR1A = 0;
    // Toggle timer 1 pin for a few us
    digitalWrite(PWM_1, HIGH);
    delayMicroseconds(us);
    digitalWrite(PWM_1, LOW);
    // Set timer 1 pin linked to output compare
    TCCR1A = _BV(COM1A1) | _BV(WGM11);
}
