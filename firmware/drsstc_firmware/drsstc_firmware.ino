#include "drsstc_firmware.h"

// Pin definitions
#define NEOPIXEL    2
#define PWM_1       9 // Labeled 'B' on board
#define PWM_2       3 // Labeled 'A' on board
#define OCD_DETECT  8
#define LED1       10
#define LED2       11
#define MSTR_EN    A0
#define MODE_IN    A1
#define TEST_IN    A2

// Setup neopixel ring
LEDRing led_ring(NEOPIXEL);
void led_ring_process_instruction(const LEDInstruction& inst) {
  led_ring.process(inst);
}
bool play_music_with_led() {
  return play_midi(&led_ring_process_instruction);
}

#define DAC_ADDRESS       0x60
const uint8_t INITIAL_DAC_VALUE = 0x80;
MCP47X6 DAC = MCP47X6(DAC_ADDRESS);

void setup() {
  // Set pin directions
  pinMode(NEOPIXEL, OUTPUT);
  pinMode(PWM_1, OUTPUT);
  pinMode(PWM_2, OUTPUT);
  pinMode(OCD_DETECT, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(MSTR_EN, INPUT);
  pinMode(MODE_IN, INPUT);
  pinMode(TEST_IN, INPUT);

  // Initialize output pins
  digitalWrite(PWM_1, LOW);
  digitalWrite(PWM_2, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);

  // Initialize I2C bus
  Wire.begin();
  TWBR = 12;
  
  // Initialize MCP47X6 DAC on I2C bus
  DAC.begin();
  DAC.begin();
  DAC.setVReference(MCP47X6_VREF_VDD);
  DAC.setGain(MCP47X6_GAIN_1X);
  DAC.saveSettings();
  DAC.setOutputLevel(INITIAL_DAC_VALUE);

  // Initialize timer1/timer2 outputs for interrupter
  setup_timers();
}

// State machine
#define STARTUP     0
#define LIGHT_SHOW  1  // LEDs running but no pulses
#define SLOW_PULSE  2  // Long, slow pulses with LEDs off
#define MUSIC_PLAY  3  // Playing a song from memory
#define MUSIC_PAUSE 4  // Paused during playback
#define MUSIC_INT   5  // In between songs
#define TEST_MODE   6
#define SHUTDOWN    7

int current_state = STARTUP;
unsigned long last_state_change = 0;

#define MINUTE             60000
#define LIGHT_SHOW_TIMEOUT (60 * MINUTE)
#define SLOW_PULSE_TIMEOUT (20 * MINUTE)
#define MUSIC_TIMEOUT      (10 * MINUTE)
#define MUSIC_PAUSE_TIMEOUT (5 * MINUTE)
#define MUSIC_INT_PERIOD   10000  // 10s between songs

inline void change_state(int new_state) {
  last_state_change = millis();
  current_state = new_state;
}

void cancel_test_mode() {
  led_ring.reset();
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
}

void update_state_machine() {
  // Update state machine
  switch (current_state) {
    case STARTUP:
      // Run switch must be off to initialize
      if (digitalRead(MSTR_EN) == LOW) {
        change_state(LIGHT_SHOW);
      } else if (digitalRead(TEST_IN) == HIGH) {
        change_state(TEST_MODE);
      }
      break;
    case LIGHT_SHOW:
      if (digitalRead(TEST_IN) == HIGH) {
        change_state(TEST_MODE);
      } else if (digitalRead(MSTR_EN) == HIGH) {
        // When the run switch is first engaged, determine the mode
        led_ring.reset();
        switch (digitalRead(MODE_IN)) {
          case LOW:  change_state(SLOW_PULSE); break;
          case HIGH: change_state(MUSIC_PLAY); break;
        }
      } else if (millis() - last_state_change > LIGHT_SHOW_TIMEOUT) {
        change_state(SHUTDOWN);
      }
      break;
    case SLOW_PULSE:
      if (digitalRead(MSTR_EN) == LOW) {
        change_state(LIGHT_SHOW);
      } else if (millis() - last_state_change > SLOW_PULSE_TIMEOUT) {
        change_state(SHUTDOWN);
      }
      break;
    case MUSIC_PLAY:
      if (digitalRead(MSTR_EN) == LOW) {
        pause_midi();
        change_state(MUSIC_PAUSE);
      } else if (millis() - last_state_change > MUSIC_TIMEOUT) {
        change_state(SHUTDOWN);
      }
      break;
    case MUSIC_PAUSE:
      if (digitalRead(MODE_IN) == LOW) {
        change_state(LIGHT_SHOW);
      } else if (digitalRead(MSTR_EN) == HIGH) {
        resume_midi();
        change_state(MUSIC_PLAY);
      } else if (millis() - last_state_change > MUSIC_PAUSE_TIMEOUT) {
        change_state(LIGHT_SHOW);
      }
      break;
    case MUSIC_INT:
      if (millis() - last_state_change > MUSIC_INT_PERIOD) {
        switch (digitalRead(MSTR_EN)) {
          case LOW: change_state(MUSIC_PAUSE);
          case HIGH: change_state(MUSIC_PLAY);
        }
      }
      break;
    case TEST_MODE:
      if (digitalRead(TEST_IN) == LOW) {
        cancel_test_mode();
        change_state(STARTUP);
      }
  }
}

void slow_pulse() {
  set_timer1_prescale(0x05); // CS bits = 0x05 = 1024x prescaler
  OCR1A = 2;   // 128us pulses 
  ICR1 = 1500; // 10.4 Hz frequency
  OCR2B = 0;
  led_ring.turn_off_leds();
}

#define NOTE_A4 69
#define LED_TEST_DELAY 500
time_t led_timer = 0;
uint8_t led_phase = 0;
void test_mode() {
  led_ring.light_show();
  play_midi_note(NOTE_A4, 1, true);
  time_t timestamp = millis();
  if (led_timer == 0) led_timer = timestamp;
  if (timestamp - led_timer > LED_TEST_DELAY) {
    led_phase++;
    digitalWrite(LED1,(led_phase & 1) ? HIGH : LOW);
    digitalWrite(LED2,(led_phase & 2) ? HIGH : LOW);
    led_timer = timestamp;    
  }
}

void loop() {
  update_state_machine();
  switch (current_state) {
    case LIGHT_SHOW: 
    case MUSIC_INT:
      led_ring.light_show(); break;
    case SLOW_PULSE: 
      slow_pulse(); break;
    case MUSIC_PLAY:
      if (!play_music_with_led()) change_state(MUSIC_INT);
      break;
    case TEST_MODE: 
      test_mode(); break;
  }
}
