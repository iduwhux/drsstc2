#pragma once

#include <Adafruit_NeoPixel.h>

// LED segments
// Single LEDs from 0x00-0x0f
#define NUM_LEDS    16
#define ALL       0x10
#define EVEN      0x11
#define ODD       0x12
// From QUADS to QUADS + 3 (0x16)
#define QUADS     0x13

// Control 'segments'
#define RESET     0x17  // Resets all segments
#define ALL_INDIV 0x18  // Followed by NUM_LEDS individual colors

// Rotation 'segments'
#define INDIV_ROT    0x19
#define QUAD_ROT     0x1a
#define EVEN_ODD_ROT 0x1b

// Preprogrammed colors
#define NUM_COLORS 21
extern const byte COLOR_WHEEL[] PROGMEM;

// State of a single LED
struct LEDState {
  bool active = false;
  byte red    = 0;
  byte green  = 0;
  byte blue   = 0;

  LEDState() = default;
  void reset();
};

// Encodes flashing/fading logic for an LED segment (w/1 or more LEDs)
struct LEDSegment {
  LEDState main;                // Background color
  LEDState alternate;           // Foreground color
  unsigned long timer_start  = 0;      // Timer for flash/fade
  unsigned long timer_length = 0;      // Length of flash/fade
  bool   flashing     = false;
  bool   flash_phase  = false;  // If true, display foreground
  bool   fading       = false;

  void reset();
  void set_solid();
};

// Stores the state of a rotation for some LED segment
struct LEDRotation {
  int    current_index   = 0;
  int    step_size       = 0;
  unsigned long last_rotation   = 0;
  unsigned long rotation_period = 0;
  bool   disable         = true;

  void reset();
  void update(unsigned long timestamp);
  int apply_to_led(int led_index);
};

// Represents all 16 LEDs in the ring with multiple segments/rotations
class LEDRing {
public:
  // Segments (1 or more LEDs)
  LEDSegment individual[NUM_LEDS];
  LEDSegment all;
  LEDSegment even;
  LEDSegment odd;
  LEDSegment quads[4];

  // Rotations
  LEDRotation individual_rot;
  LEDRotation quad_rot;
  LEDRotation even_odd_rot;

  // Constructor from NEOPIXEL pin number
  LEDRing(int pin);

  // Reset all state data
  void reset_state();

  // Set all LED outputs to 0x000000
  void turn_off_leds();

  // Reset all state data and turn off LEDs
  void reset();

  // Update LEDs
  void update();

  // Cycle through the wheel of standard colors
  void light_show();

  // Display a varying number of LEDs
  void bar_graph(unsigned int count, byte r, byte b, byte g);

  // Read binary instruction data from MIDI stream
  const byte* read_midi_data(const byte* pointer, size_t n_instructions);
  
private:
  Adafruit_NeoPixel strip;
};

// Single main instance for LEDRing
//extern LEDRing led_ring;
