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

namespace {
  void apply_instruction_to_rotation(const LEDInstruction& inst, const time_t timestamp, LEDRotation& rot) {
    if (inst.set_start) rot.current_index = inst.start_idx;
    rot.step_size = (inst.segment == ROT_LEFT) ? -(int)inst.step_size : inst.step_size;
    rot.last_rotation = timestamp;
    rot.rotation_period = inst.time_ms;
    rot.disable = inst.disable;
  }
}

void LEDRing::process(const LEDInstruction& inst) {
  if (inst.segment == RESET) {
    reset_state(); return;
  }
  time_t timestamp = millis();
  LEDSegment* segment = nullptr;
  if (inst.segment < NUM_LEDS) {
    segment = &individual[inst.segment];
  }
  switch (inst.segment) {
    case ALL: segment = &all; break;
    case EVEN: segment = &even; break;
    case ODD: segment = &odd; break;
  }
  if (inst.segment >= QUADS && inst.segment < QUADS + 4) {
    segment = &quads[inst.segment - QUADS];
  }
  if (segment) {
    if (inst.flash || inst.fade) {
      segment->alternate = inst;
      segment->timer_start = timestamp;
      segment->timer_length = inst.time_ms;
      segment->flashing = inst.flash;
      segment->fading = inst.fade;
    } else {
      segment->main = inst;
      if (inst.solid) {
        segment->timer_start = 0;
        segment->timer_length = 0;
        segment->flashing = false;
        segment->fading = false;
      }
    }
  } else if (inst.segment == ROT_LEFT || inst.segment == ROT_RIGHT) {
    if (inst.apply_to_individual) apply_instruction_to_rotation(inst, timestamp, individual_rot);
    if (inst.apply_to_quad)       apply_instruction_to_rotation(inst, timestamp, quad_rot);
    if (inst.apply_to_even_odd)   apply_instruction_to_rotation(inst, timestamp, even_odd_rot);
  }
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
