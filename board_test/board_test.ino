#include <MCP47X6.h>

#include <Wire.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define NEOPIXEL_PIN 2

#define NUM_LEDS 16

#define BRIGHTNESS 50

#define LED1_PIN 10
#define LED2_PIN 11
#define NUM_COLORS 6

byte color_wheel[][3] = {{255, 0, 0}, 
                         {255, 255, 0}, 
                         {0, 255, 0}, 
                         {0, 255, 255}, 
                         {0, 0, 255},
                         {255, 0, 255}};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

int current_color = 0;

void set_neopixel(int pixel, double t = 0.0) {
  double rgb[] = {0.0, 0.0, 0.0};
  for (int i = 0; i < 3; i++) rgb[i] = (double)color_wheel[current_color][i];
  if (t != 0.0) {
    int next_color = (t > 0.0) ? current_color + 1 : current_color - 1;
    if (next_color < 0) next_color = NUM_COLORS - 1;
    if (next_color >= NUM_COLORS) next_color = 0;
    for (int i = 0; i < 3; i++)
      rgb[i] += t * ((double)color_wheel[next_color][i] - (double)color_wheel[current_color][i]);
  }
  for (int i = 0; i < 3; i++) {
    if (rgb[i] < 0.0) rgb[i] = 0.0;
    if (rgb[i] > 255.0) rgb[i] = 255.0;
  }
  strip.setPixelColor(pixel, (byte)rgb[0], (byte)rgb[1], (byte)rgb[2]);
}

#define COLOR_CYCLE_MS_PER_PIXEL 150
#define DAC_UPDATE_MS 2000
unsigned long current_pixel_start = 0;
unsigned long last_update_ms = 0;
unsigned long last_dac_update = 0;
unsigned long last_timer_pin_change = 0;

const byte DAC_ADDRESS = 0x60;
MCP47X6 DAC=MCP47X6(DAC_ADDRESS);
uint8_t dac_value = 1;

void setup() {
  // put your setup code here, to run once:
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  for (int i = 0; i < NUM_LEDS; i++) set_neopixel(i);
  strip.show();
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  Wire.begin();  // I2C
  TWBR = 12;
  DAC.begin();
  DAC.setVReference(MCP47X6_VREF_VDD);
  DAC.setGain(MCP47X6_GAIN_1X);
  DAC.saveSettings();
  DAC.setOutputLevel(dac_value);

  pinMode(9, OUTPUT); // Timer 1, output A
  // COM1A1 (0x80) = non-inverted PWM output to channel A (pin 9)
  // WGM11 (0x02) = fast PWM mode, ICR1 as TOP
  TCCR1A = _BV(COM1A1) | _BV(WGM11);
  // WGM13 + WGM12 (0x18) = fast PWM mode w/ICR1 top
  // CS10 (0x01) = no prescaling
  TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10);

  // PWM hi for 64 cycles = 4 us
  OCR1A = 64;
  // PWM frequency = 440 Hz (A)
  ICR1 = 36363;

  pinMode(3, OUTPUT); // Timer 2, output B
  // COM2B1 (0x20) = non-inverted PWM output to channel B (pin 3)
  // WGM21 + WGM20 (0x03) = fast PWM mode
  TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  // WGM22 (0x08) = fast PWM w/ OCR2A top
  // CS22 + CS21 + CS20 (0x07) = 1024x prescaler
  TCCR2B = _BV(WGM22) | _BV(CS22) | _BV(CS21) | _BV(CS20);

  // PWM hi for 1024 cycles = 64 us
  OCR2B = 1;
  // PWM frequency = 62.5 Hz
  OCR2A = 250;
  
  last_update_ms = millis();
  current_pixel_start = millis();
  last_dac_update = millis();
  last_timer_pin_change = millis();
}

int status_led_counter = 0;
#define DELAY_MS 200

int current_pixel = 0;

int timer_pin_phase = 0;
#define TIMER_PIN_DELAY 500

void loop() {
  if (millis() - last_update_ms > DELAY_MS) {
    status_led_counter++;
    if (status_led_counter >= 4) {
      status_led_counter = 0;
    }
    last_update_ms = millis();
  }
  digitalWrite(LED1_PIN, int(status_led_counter / 2) == 0 ? LOW : HIGH);
  digitalWrite(LED2_PIN, status_led_counter % 2 == 0 ? LOW : HIGH);
  if (millis() - last_dac_update > DAC_UPDATE_MS) {
    if (dac_value < 128) {
      dac_value = dac_value << 1;
    } else if (dac_value == 128) {
      dac_value = 255;
    } else {
      dac_value = 1;
    }
    DAC.setOutputLevel(dac_value);
    last_dac_update = millis();
  }

/*
  if (millis() - last_timer_pin_change > TIMER_PIN_DELAY) {
    timer_pin_phase++;
    if (timer_pin_phase >= 4) timer_pin_phase = 0;
    last_timer_pin_change = millis();
  }
  digitalWrite(3, timer_pin_phase == 1 ? HIGH : LOW);
  digitalWrite(9, timer_pin_phase == 3 ? HIGH : LOW);
*/

  double t = (double)(millis() - current_pixel_start) / COLOR_CYCLE_MS_PER_PIXEL;
  if (t < 0.0) t = 0.0;
  while (t >= 1.0) {
    set_neopixel(current_pixel, 1.0);
    current_pixel++;
    if (current_pixel >= NUM_LEDS) {
      current_pixel = 0;
      current_color++;
      if (current_color >= NUM_COLORS) current_color = 0;
    }
    t -= 1.0;
    current_pixel_start = millis();
  }
  set_neopixel(current_pixel, t);
  
  strip.show();
}
