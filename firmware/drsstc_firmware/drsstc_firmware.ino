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
#define TRIG_IN    A3

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
  pinMode(TRIG_IN, INPUT);

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
          case LOW:  
            change_state(SLOW_PULSE); 
            break;
          case HIGH: 
            load_next_song();
            change_state(MUSIC_PLAY); 
            break;
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
        load_next_song();
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

unsigned long test_mode_pulse_start = 0;
bool test_mode_pulse = false;
#define TEST_MODE_PULSE_LENGTH 10   // microseconds
#define TEST_MODE_PULSE_DELAY 1000  // milliseconds

void test_mode() {
  led_ring.light_show();
  set_pwm_off();
  if (test_mode_pulse) {
    if (test_mode_pulse_start + TEST_MODE_PULSE_DELAY >= millis()) {
      test_mode_pulse = false;
      test_mode_pulse_start = 0;
    }
  } else {
    if (digitalRead(MSTR_EN) == HIGH && digitalRead(TRIG_IN) == HIGH) {
      // Set timer 1 pin manual
      TCCR1A = 0;
      // Toggle timer 1 pin for a few us
      digitalWrite(PWM_1, HIGH);
      delayMicroseconds(TEST_MODE_PULSE_LENGTH);
      digitalWrite(PWM_1, LOW);
      // Set timer 1 pin linked to output compare
      TCCR1A = _BV(COM1A1) | _BV(WGM11);

      test_mode_pulse = true;
      test_mode_pulse_start = millis();
    }
  }
}

unsigned long last_flash_ms = 0;
bool status_leds[2] = {false, false};

#define FLASH_DELAY 250

void flash_status() {
  unsigned long timestamp = millis();
  bool flash_change = (last_flash_ms == 0 || timestamp >= last_flash_ms + FLASH_DELAY);
  if (flash_change) last_flash_ms = timestamp;
  switch (current_state) {
    case STARTUP:
      // At startup, both LEDs flash synchronously
      if (flash_change) {
        status_leds[0] = !status_leds[0];
        status_leds[1] = status_leds[0];
      }
      break;
    case LIGHT_SHOW:
      // During the light show state, only the second LED flashes
      status_leds[0] = false;
      if (flash_change) status_leds[1] = !status_leds[1];
      break;
    // One or the other LED is solid during "normal" operation modes
    case SLOW_PULSE:
      status_leds[0] = true;
      status_leds[1] = false;
      break;
    case MUSIC_PLAY:
    case MUSIC_PAUSE:
    case MUSIC_INT:
      status_leds[0] = false;
      status_leds[1] = true;
      break;
    case TEST_MODE:
      // In test mode, only the first LED flashes
      if (flash_change) status_leds[0] = !status_leds[0];
      // The second LED pulses when a test pulse is sent
      status_leds[1] = test_mode_pulse;
      break;
    case SHUTDOWN:
      // In the shutdown state, both LEDs flash asynchronously
      if (flash_change) {
        status_leds[0] = !status_leds[0];
        status_leds[1] = !status_leds[0];
      }
      break;
  }
  digitalWrite(LED1, status_leds[0] ? HIGH : LOW);
  digitalWrite(LED2, status_leds[1] ? HIGH : LOW);
}

void loop() {
  update_state_machine();
  flash_status();
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
