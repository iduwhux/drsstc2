#include "LEDRing.h"

void LEDState::reset() {
  red = 0;
  green = 0;
  blue = 0;
  active = false;
}

void LEDSegment::reset() {
  main.reset();
  set_solid();
}

void LEDSegment::set_solid() {
  alternate.reset();
  timer_start = 0;
  timer_length = 0;
  flashing = false;
  flash_phase = false;
  fading = false;
}

void LEDRotation::reset() {
  current_index = 0;
  step_size = 0;
  last_rotation = 0;
  rotation_period = 0;
  disable = true;
}

void LEDRotation::update(unsigned long timestamp) {
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

#define DEFAULT_BRIGHTNESS 50

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
    individual[i].reset();
  }
  all.reset();
  even.reset();
  odd.reset();
  for (int i = 0; i < 4; i++) {
    quads[i].reset();
  }
  individual_rot.reset();
  quad_rot.reset();
  even_odd_rot.reset();
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
  
  void apply_segment_to_state(LEDSegment& segment, unsigned long timestamp, LEDState& state) {
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
  unsigned long timestamp = millis();
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

  const byte* read_ms_from_midi_data(const byte* pointer, unsigned long& ms) {
    byte time_period = *(pointer++);
    bool long_scale = time_period & 0x80;
    unsigned long t = time_period & 0x7f;
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
    if (segment >= INDIV_ROT && segment <= EVEN_ODD_ROT) {
      LEDRotation& rot = individual_rot;
      switch (segment) {
        case QUAD_ROT: rot = quad_rot; break;
        case EVEN_ODD_ROT: rot = even_odd_rot; break;
      }
      if (seg_byte & 0x80) {
        rot.reset();
      } else {
        byte index_pos = *(pointer++);
        while (index_pos >= NUM_LEDS) index_pos -= NUM_LEDS;
        rot.current_index = index_pos;
        if (seg_byte & 0x40) { // Moving
          rot.last_rotation = millis();
          rot.step_size = (seg_byte & 0x20) ? 1 : -1;
          pointer = read_ms_from_midi_data(pointer, rot.rotation_period);
        } else {               // Static
          rot.last_rotation = 0;
          rot.step_size = 0;
          rot.rotation_period = 0;
        }
        rot.disable = false;
      }
      bool moving  = seg_byte  & 0x40; // If false, only a single index position is read
      byte index_position = *(pointer++);
    } else {
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
    }

    return pointer;
  }
}

extern const byte COLOR_WHEEL[] PROGMEM = 
  {255,   0,   0,   // red
   255,  28,   0,
   255,  57,   0,
   255,  85,   0,   // orange
   255, 142,   0,
   255, 198,   0,
   255, 255,   0,   // yellow
   170, 255,   0,
    85, 255,   0,
     0, 255,   0,   // green
     0, 170,  85,
     0,  85, 170,
     0,   0, 255,   // blue
    28,   0, 255,
    57,   0, 255,
    85,   0, 255,   // indigo
   142,   0, 255,
   198,   0, 255,
   255,   0, 255,   // violet
   255,   0, 170,
   255,   0,  85};

namespace {
  unsigned long last_update = 0;
  double last_offset = 0.0;
}

#define LIGHT_SHOW_ROT_PERIOD 2000

void LEDRing::light_show() {
  unsigned long timestamp = millis();
  if (last_update == 0 || last_update > timestamp) last_update = timestamp;
  double t_offset = last_offset + (double)(timestamp - last_update) / (LIGHT_SHOW_ROT_PERIOD * NUM_LEDS);
  while (t_offset < 0) t_offset += NUM_COLORS;
  while (t_offset >= NUM_COLORS) t_offset -= NUM_COLORS;
  last_offset = t_offset;
  last_update = timestamp;

  for (unsigned int i = 0; i < NUM_LEDS; i++) {
    int t = (int)((double)(i) * NUM_COLORS / NUM_LEDS + t_offset);
    while (t < 0) t += NUM_COLORS;
    while (t >= NUM_COLORS) t -= NUM_COLORS;
    individual[i].main.red   = COLOR_WHEEL[3 * t];
    individual[i].main.green = COLOR_WHEEL[3 * t + 1];
    individual[i].main.blue  = COLOR_WHEEL[3 * t + 2];
  }
  
  update();
}

void LEDRing::bar_graph(unsigned int count, byte r, byte b, byte g) {
  reset();
  all.main.red = 0;
  all.main.blue = 0;
  all.main.green = 0;
  for (unsigned int i = 0; i < count; i++) {
    individual[i].main.red = r;
    individual[i].main.blue = b;
    individual[i].main.green = g;
  }
  update();
}
