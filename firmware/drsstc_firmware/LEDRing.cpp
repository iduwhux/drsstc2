#include "pin_definitions.h"
#include "LEDRing.h"

#define DEFAULT_BRIGHTNESS 50

Adafruit_NeoPixel led_strip(NUM_LEDS, NEOPIXEL, NEO_GRB + NEO_KHZ800);

void init_led_strip() {
    // Initialize Neopixel strip
  led_strip.setBrightness(DEFAULT_BRIGHTNESS);
  led_strip.begin();
  for (int i = 0; i < NUM_LEDS; i++) led_strip.setPixelColor(i, 0, 0, 0);
  led_strip.show();
}


void metronome_background(unsigned int pixel) {
  unsigned int seq = (pixel + NUM_LEDS - METRONOME_OFFSET) & NUM_LED_MASK;
  if (seq & 0x03 == 0) {
    // bar = white
    led_strip.setPixelColor(pixel, 255, 255, 255);
  } else if (seq & 0x01 == 0) {
    // off-beat = green
    led_strip.setPixelColor(pixel, 0, 255, 0);
  } else {
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

  // Active beat is red
  led_strip.setPixelColor(on_pixel, 255, 0, 0);
  // Reset previous beat
  metronome_background(off_pixel);
  
  led_strip.show();
}

namespace {
  #define LED_CYCLE_LENGTH 5000
  
  unsigned long prev_led_cycle_mark = 0; // milliseconds
}

void led_strip_cycle() {
  
}
