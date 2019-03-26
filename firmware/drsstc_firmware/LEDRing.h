#pragma once

#include <arduino.h>
#include "TimeSignature.h"
#include <Adafruit_NeoPixel.h>

// State of a single LED
struct LEDState {
  bool active = false;
  byte red    = 0;
  byte green  = 0;
  byte blue   = 0;

  LEDState() = default;
  
  // Initialize from instruction (4-bit to 8-bit conversion)
  LEDState(const LEDInstruction& inst) :
    active(!inst.disable), 
    red(inst.red << 4), 
    green(inst.green << 4), 
    blue(inst.blue << 4) { }
};

// Encodes flashing/fading logic for an LED segment (w/1 or more LEDs)
struct LEDSegment {
  LEDState main;                // Background color
  LEDState alternate;           // Foreground color
  time_t timer_start  = 0;      // Timer for flash/fade
  time_t timer_length = 0;      // Length of flash/fade
  bool   flashing     = false;
  bool   flash_phase  = false;  // If true, display foreground
  bool   fading       = false;
};

// Stores the state of a rotation for some LED segment
struct LEDRotation {
  int    current_index   = 0;
  int    step_size       = 0;
  time_t last_rotation   = 0;
  time_t rotation_period = 0;
  bool   disable         = true;

  void update(time_t timestamp);
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

  // Update segments/rotations from instruction
  void process(const LEDInstruction& inst);

  // Reset all state data
  void reset_state();

  // Set all LED outputs to 0x000000
  void turn_off_leds();

  // Reset all state data and turn off LEDs
  void reset();

  // Update LEDs
  void update();

  void light_show();
private:
  Adafruit_NeoPixel strip;
};
