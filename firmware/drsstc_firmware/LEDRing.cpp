#include <Adafruit_NeoPixel.h>

#include "pin_definitions.h"
#include "LEDRing.h"

#define DEFAULT_BRIGHTNESS 50

Adafruit_NeoPixel led_strip(NUM_LEDS, NEOPIXEL, NEO_GRB + NEO_KHZ800);

void init_led_strip() {
    // Initialize Neopixel strip
  led_strip.setBrightness(DEFAULT_BRIGHTNESS);
  led_strip.begin();
  reset_led_strip();
}

void reset_led_strip() {  
  led_strip.fill(0);
  led_strip.show();
}


void metronome_background(unsigned int pixel) {
  unsigned int seq = (pixel + NUM_LEDS - METRONOME_OFFSET) & NUM_LED_MASK;
  if (seq & 0x03 == 0) {
    // bar-beat = white
    led_strip.setPixelColor(pixel, 255, 255, 255);
  } else if (seq & 0x01 == 0) {
    // off-beat = green
    led_strip.setPixelColor(pixel, 0, 255, 0);
  } else {
    // all others off
    led_strip.setPixelColor(pixel, 0, 0, 0);
  }
}

void init_led_metronome() {
  for (unsigned int pixel = 0; pixel < NUM_LEDS; pixel++) {
    metronome_background(pixel);
  }
  led_strip.show();
}

void led_metronome_beat(unsigned int beat_num) {
  const unsigned int on_pixel = (beat_num + METRONOME_OFFSET) & NUM_LED_MASK;
  const unsigned int off_pixel = (on_pixel + NUM_LEDS - 1) & NUM_LED_MASK;

  // Reset previous beat
  metronome_background(off_pixel);
  // Active beat is red
  led_strip.setPixelColor(on_pixel, 255, 0, 0);
    
  led_strip.show();
}

namespace {
  #define LED_ANIMATION_FRAMESTEP 20
  #define LED_CYCLE_LENGTH 5000
  #define MAX_HUE 65536

  unsigned long led_animation_mark = 0;
  unsigned long led_animation_index = 0;

  void paint_led_strip_cycle() {
    for (unsigned int pixel = 0; pixel < NUM_LEDS; pixel++) {
      uint16_t hue = led_animation_index + pixel * MAX_HUE / NUM_LEDS;
      uint32_t color = led_strip.ColorHSV(hue);
      led_strip.setPixelColor(pixel, color);
    }
    led_strip.show();
  }
}

void init_led_strip_cycle() {
  led_animation_mark = millis();
  led_animation_index = 0;
  paint_led_strip_cycle();
}

void led_strip_cycle() {
  unsigned long timestamp = millis();
  if (led_animation_mark == 0 || led_animation_mark > timestamp) led_animation_mark = timestamp;
  if (led_animation_mark + LED_ANIMATION_FRAMESTEP > timestamp) return;
  led_animation_index += ((led_animation_mark - timestamp) * MAX_HUE) / LED_CYCLE_LENGTH;
  led_animation_mark = timestamp;
  paint_led_strip_cycle();
}

namespace {
  uint16_t led_flash_hue = 0;
  unsigned long led_flash_period = 0; 
}

void led_strip_solid(uint16_t hue) {
  led_strip.fill(led_strip.ColorHSV(hue));
  led_strip.show();  
}

void init_led_strip_flash(uint16_t hue, unsigned long period) {
  led_flash_hue = hue;
  led_flash_period = period;
  led_animation_mark = millis();
  led_animation_index = 0;
  reset_led_strip();
}

void led_strip_flash() {
  unsigned long timestamp = millis();
  if (led_animation_mark == 0 || led_animation_mark > timestamp) led_animation_mark = timestamp;  
  if (led_animation_mark + led_flash_period > timestamp) return;
  led_animation_mark += led_flash_period;
  led_animation_index = 1 - led_animation_index;
  if (led_animation_index) {
    led_strip.fill(led_strip.ColorHSV(led_flash_hue));
    led_strip.show();
  } else {
    reset_led_strip();
  }
}
