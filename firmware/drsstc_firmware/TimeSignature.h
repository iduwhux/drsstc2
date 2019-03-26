#pragma once

#include <stdint.h>
typedef unsigned long time_t;

// TimeSignature opcodes
// 0x00 is NOOP
#define TONE       0x01  // Change frequency (followed by 8-bit MIDINote)
#define VOLUME     0x02  // Change volume (followed by 8-bit volume)
#define SLIDE_TO   0x04  // Activate slide to tgt note (followed by 8-bit MIDINote and 8-bit number of beats)
#define SLIDE_FROM 0x08  // Reverse slide from tgt note to current, use 0x0C for bending

typedef struct __attribute__((packed)) {
  uint8_t opcode1           : 4;  // opcode for timer1
  uint8_t opcode2           : 4;  // opcode for timer2
  bool end_program          : 1;  // if true, this is the final instruction in the buffer
  bool timer1_equals_timer2 : 1;  // if true, save space by using one value for both timers
  bool change_tempo         : 1;
  uint8_t num_led_inst      : 5;  // Up to 32 LEDInstruction structs to follow
  uint16_t beat_number      : 16; // 64 beats/bar, up to 1024 bars      
} TimeSignature;  // 32-bit

// LED segments for LEDInstruction
// Single LEDs from 0x00-0x0f
#define NUM_LEDS   16
#define ALL      0x10
#define EVEN     0x11
#define ODD      0x12
// From QUADS to QUADS + 3 (0x16)
#define QUADS  0x13

// These 'segments' are used to signal the rotation control
#define ROT_LEFT  0x17
#define ROT_RIGHT 0x18

#define RESET     0x19

typedef struct __attribute__((packed)) {
  bool flash   : 1;
  bool fade    : 1;
  bool solid   : 1;
  byte segment : 5;
  bool disable : 1;
  time_t time_ms : 11; // 0 - 2047 ms for flash/fade/rotate periods
  union {
    struct {
      bool apply_to_individual : 1;
      bool apply_to_quad       : 1;
      bool apply_to_even_odd   : 1;
      bool set_start           : 1; // Use start_idx values
      byte start_idx           : 4; // Initial LED 0-15
      byte step_size           : 4; // Step size 0-15
    };
    struct {
      byte red     : 4;
      byte green   : 4;
      byte blue    : 4;
    };
  };
} LEDInstruction;  // 32-bit

typedef struct __attribute__((packed)) {
  bool en : 1;
  uint8_t note : 7;
} MIDINote; // 8-bit
