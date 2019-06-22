#pragma once

#include <Adafruit_NeoPixel.h>

#define NUM_LEDS    16
#define NUM_LED_MASK 0x0f
#define METRONOME_OFFSET 0

extern Adafruit_NeoPixel led_strip;

void init_led_strip();

void reset_led_strip();

void init_led_strip_cycle();

void led_strip_cycle();

void led_strip_solid(uint16_t hue);

void init_led_strip_flash(uint16_t hue, unsigned long period);

void led_strip_flash();

void init_led_metronome();

void led_metronome_beat(unsigned int beat_num);
