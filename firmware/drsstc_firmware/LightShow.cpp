#include "LEDRing.h"

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
  time_t last_update = 0;
  double last_offset = 0.0;
}

#define LIGHT_SHOW_ROT_PERIOD 2000

void LEDRing::light_show() {
  time_t timestamp = millis();
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
