#include "LEDRing.h"

#define DEFAULT_BRIGHTNESS 50

void LEDRotation::update(time_t timestamp) {
  if (disable || rotation_period == 0) return;
  if (last_rotation == 0) last_rotation = timestamp;
  while (timestamp > last_rotation + rotation_period) {
    current_index += step_size;
    while (current_index < 0) current_index += NUM_LEDS;
    while (current_index >= NUM_LEDS) current_index -= NUM_LEDS;
    last_rotation += rotation_period;
  }
}

int LEDRotation::apply_to_led(int led_index) {
  if (disable) return led_index;
  int new_index = led_index + current_index;
  while (new_index >= NUM_LEDS) new_index -= NUM_LEDS;
  return new_index;
}

// Constructor for LEDRing
LEDRing::LEDRing(int pin) : strip(NUM_LEDS, pin, NEO_GRB + NEO_KHZ800) { 
  // Initialize Neopixel strip
  strip.setBrightness(DEFAULT_BRIGHTNESS);
  strip.begin();
  for (int i = 0; i < NUM_LEDS; i++) strip.setPixelColor(i, 0, 0, 0);
  strip.show();
}

void LEDRing::reset_state() {
  for (int i = 0; i < NUM_LEDS; i++) {
    individual[i] = LEDSegment();
  }
  all = LEDSegment();
  even = LEDSegment();
  odd = LEDSegment();
  for (int i = 0; i < 4; i++) {
    quads[i] = LEDSegment();
  }
  individual_rot = LEDRotation();
  quad_rot = LEDRotation();
  even_odd_rot = LEDRotation();
}

void LEDRing::turn_off_leds() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();  
}

void LEDRing::reset() {
  reset_state();
  turn_off_leds();
}

namespace {
  LEDState blend_state(const LEDState& state1, const LEDState& state2, double t) {
    if (t < 0) t = 0;
    if (t > 1) t = 1;
    LEDState state_copy = state2;
    state_copy.red = state1.red + (byte)((state2.red - state1.red) * t);
    state_copy.blue = state1.blue + (byte)((state2.blue - state1.blue) * t);
    state_copy.green = state1.green + (byte)((state2.green - state1.green) * t);
    return state_copy;
  }

  void apply_state(const LEDState& overlay, LEDState& orig) {
    if (overlay.active) orig = overlay;
  }
  
  void apply_segment_to_state(LEDSegment& segment, time_t timestamp, LEDState& state) {
    double t = 
      (timestamp < segment.timer_start) ? 0 : (double)(timestamp - segment.timer_start)
        / (segment.timer_length > 0 ? segment.timer_length : 1000);  // 1000 ms default
    if (t > 1.0) {
      if (segment.flashing) {
        segment.flash_phase = !segment.flash_phase;
      } else if (segment.fading) {
        segment.main = segment.alternate;
        segment.timer_start = 0;
        segment.timer_length = 0;
        segment.fading = false;
      }
    }
    if (segment.flashing && segment.alternate.active) {
      apply_state(segment.flash_phase ? segment.alternate : segment.main, state);
    } else if (segment.fading && segment.alternate.active) {
      apply_state(blend_state(segment.main, segment.alternate, t), state);
    } else {
      apply_state(segment.main, state);
    }
  }
}

void LEDRing::update() {
  time_t timestamp = millis();
  individual_rot.update(timestamp);
  quad_rot.update(timestamp);
  even_odd_rot.update(timestamp);

  for (int i = 0; i < NUM_LEDS; i++) {
    LEDState state;
    apply_segment_to_state(all, timestamp, state);

    int quad_index = (quad_rot.apply_to_led(i) * 4) / NUM_LEDS;
    apply_segment_to_state(quads[quad_index], timestamp, state);

    switch (even_odd_rot.apply_to_led(i) % 2) {
      case 0: apply_segment_to_state(even, timestamp, state); break;
      case 1: apply_segment_to_state(odd,  timestamp, state); break;
    }
    apply_segment_to_state(individual[individual_rot.apply_to_led(i)],     timestamp, state);

    if (state.active) {
      strip.setPixelColor(i, state.red, state.green, state.blue);
    }
  }
  strip.show();
}

void LEDState::reset() {
  red = 0;
  green = 0;
  blue = 0;
  active = false;
}

void LEDSegment::set_solid() {
  alternate.reset();
  timer_start = 0;
  timer_length = 0;
  flashing = false;
  flash_phase = false;
  fading = false;
}

void LEDSegment::reset() {
  main.reset();
  set_solid();
}

#define SOLID_COLOR   0
#define FLASHING      1
#define FADING        2
#define RESET_SEGMENT 3

namespace {
  const byte* read_state_from_midi_data(const byte* pointer, bool color_wheel, LEDState& state) {
    if (color_wheel) {
      byte wheel_index = *(pointer++);
      if (wheel_index < NUM_COLORS) {
        state.red   = COLOR_WHEEL[wheel_index * 3];
        state.green = COLOR_WHEEL[wheel_index * 3 + 1];
        state.blue  = COLOR_WHEEL[wheel_index * 3 + 2];
      }
    } else {
      state.red   = *(pointer++);
      state.green = *(pointer++);
      state.blue  = *(pointer++);
    }
    state.active = true;

    return pointer;
  }

  const byte* read_ms_from_midi_data(const byte* pointer, time_t& ms) {
    byte time_period = *(pointer++);
    bool long_scale = time_period & 0x80;
    time_t t = time_period & 0x7f;
    if (long_scale) {
      ms = t << 6;  // (0-127 x64ms = 0.0-8.0s)
    } else {
      ms = t << 2;  // (0-127 x4ms  = 0.0-0.5s)
    }
    return pointer;
  }

  const byte* apply_midi_data_to_segment(const byte* pointer, LEDSegment& segment, bool color_wheel, byte behavior) {
    if (behavior == 0) {                         // SOLID
      pointer = read_state_from_midi_data(pointer, color_wheel, segment.main);
      segment.set_solid();
    } else if (behavior == 1 || behavior == 2) { // FLASHING or FADING
      pointer = read_state_from_midi_data(pointer, color_wheel, segment.main);
      pointer = read_state_from_midi_data(pointer, color_wheel, segment.alternate);
      pointer = read_ms_from_midi_data(pointer, segment.timer_length);
      segment.timer_start = millis();
      segment.flashing = (behavior == 1);
      segment.fading   = (behavior == 2);
    } else if (behavior == 3) {                 // RESET
      segment.reset();
    }
    return pointer;
  }
}

const byte* LEDRing::read_midi_data(const byte* pointer, size_t n_instructions) {
  for (size_t i = 0; i < n_instructions; i++) {
    byte seg_byte = *(pointer++);
    byte segment     = seg_byte & 0x1f;  // 5 LSB are a segment code
    if (segment == RESET) { reset(); continue; }
    if (segment == ROT_LEFT || segment == ROT_RIGHT) {
      byte init_index = *(pointer++);
      
    }

    bool color_wheel = seg_byte & 0x20;  // Bit 6 is a flag to use the color-wheel instead of RGB codes
    byte behavior    = seg_byte >> 6;    // 2 MSB
    LEDSegment* seg_ptr = nullptr;
    if (segment < NUM_LEDS) {
      pointer = apply_midi_data_to_segment(pointer, individual[segment], color_wheel, behavior);
    } else if (segment == ALL) {
      pointer = apply_midi_data_to_segment(pointer, all, color_wheel, behavior);
    } else if (segment == EVEN) {
      pointer = apply_midi_data_to_segment(pointer, even, color_wheel, behavior);
    } else if (segment == ODD) {
      pointer = apply_midi_data_to_segment(pointer, odd, color_wheel, behavior);
    } else if (segment >= QUADS && segment < QUADS + 4) {
      pointer = apply_midi_data_to_segment(pointer, quads[segment - QUADS], color_wheel, behavior);
    } else if (segment == ALL_INDIV) {
      for (size_t seg_i = 0; seg_i < NUM_LEDS; seg_i++) {
        pointer = apply_midi_data_to_segment(pointer, individual[seg_i], color_wheel, behavior);        
      }
    }

    return pointer;
  }
}
