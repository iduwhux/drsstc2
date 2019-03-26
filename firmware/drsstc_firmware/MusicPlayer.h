#pragma once

#include <arduino.h>
#include "TimeSignature.h"

void setup_timers();

void play_midi_note(uint8_t note, uint8_t volume = 1, bool timer1 = true);
inline void silence_midi(bool timer1 = true) {
  if (timer1) {
    OCR1A = 0;
  } else {
    OCR2B = 0;
  }
}

typedef void (*LEDProcessor)(const LEDInstruction&);

bool play_midi(LEDProcessor led_processor); // Returns false when song is over
void pause_midi();
void resume_midi();

// CS_bits determines prescale:
//   0x01 = 1 (no prescale)
//   0x02 = 8
//   0x03 = 64
//   0x04 = 256
//   0x05 = 1024
extern const uint16_t PRESCALE1_VALUES[];

// Default value = 1x
inline void set_timer1_prescale(uint8_t CS_bits = 1) {
  CS_bits = (CS_bits == 0) ? 1 : (CS_bits > 5 ? 5 : CS_bits);
  
  // WGM13 + WGM12 (0x18) = fast PWM mode, ICR1 as TOP
  TCCR1B = _BV(WGM13) | _BV(WGM12) | CS_bits;
}

// CS_bits determines prescale:
//   0x01 = 1 (no prescale)
//   0x02 = 8
//   0x03 = 32
//   0x04 = 64
//   0x05 = 128
//   0x06 = 256
//   0x07 = 1024
extern const uint16_t PRESCALE2_VALUES[];

// Default value = 128x
inline void set_timer2_prescale(uint8_t CS_bits = 5) {
  CS_bits = (CS_bits == 0) ? 1 : (CS_bits > 7 ? 7 : CS_bits);
  
  // WGM22 (0x08) = fast PWM mode, OCR2A as TOP
  TCCR2B = _BV(WGM22) | CS_bits;
}

inline void set_pwm_off() {
  OCR1A = 0;
  OCR2B = 0;
}
