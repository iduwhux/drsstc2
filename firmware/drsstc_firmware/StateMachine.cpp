#include "StateMachine.h"
#include <arduino.h>
#include "pin_definitions.h"
#include "LEDRing.h"
#include "MIDIPlayer.h"

#define MAX_TEST_MODE_INDEX 10
namespace {
  int current_state = STARTUP;
  unsigned long last_state_change = 0;
  unsigned long last_slow_pulse = 0;
  unsigned long last_flash_ms = 0;
  bool status_leds[2] = {false, false};
  unsigned long test_mode_pulse_start = 0;
  bool test_mode_pulse = false;
  int test_mode_index = 0;
}

void change_state(int new_state) {
  last_state_change = millis();
  current_state = new_state;
}

int get_current_state() {
  return current_state;
}

// State timeouts - if the state does not change for
// longer than the timeout, the SHUTDOWN state is entered
#define MINUTE               60000
#define LIGHT_SHOW_TIMEOUT  (60 * MINUTE)
#define SLOW_PULSE_TIMEOUT  (20 * MINUTE)
#define MUSIC_TIMEOUT       (10 * MINUTE)
#define MUSIC_PAUSE_TIMEOUT  (5 * MINUTE)
#define MUSIC_INT_PERIOD     10000  // 10s between songs
#define TEST_MODE_DEBOUNCE 250 // 0.25s delay for software debouncing

void reset_state() {
  test_mode_index = 0;
  led_ring.reset();
  change_state(STARTUP);
}

void update_state_machine() {
  // Update state machine
  switch (current_state) {
    case STARTUP:
      if (digitalRead(TEST_IN) == HIGH) {
        test_mode_index = 0;
        change_state(TEST_MODE);
      } else if (digitalRead(MSTR_EN) == LOW) {
        // Run switch must be off to initialize
        change_state(LIGHT_SHOW);
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
      if (digitalRead(TEST_IN) == LOW 
          && millis() - last_state_change > TEST_MODE_DEBOUNCE) {
        if (digitalRead(MSTR_EN) == HIGH) {
          change_state(TEST_MODE_INC);
        } else {
          reset_state();
        }
      }
      break;
    case TEST_MODE_INC:
      if (digitalRead(MSTR_EN) == LOW) {
        reset_state();
      } else if (digitalRead(TEST_IN) == HIGH
                 && millis() - last_state_change > TEST_MODE_DEBOUNCE) {
        test_mode_index++;
        if (test_mode_index > MAX_TEST_MODE_INDEX)
          test_mode_index = MAX_TEST_MODE_INDEX;
        change_state(TEST_MODE);            
      }
      break;
  }
  flash_status();
}

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
    case TEST_MODE_INC:
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

#define SLOW_PULSE_LENGTH    20 // microseconds
#define SLOW_PULSE_DELAY    500 // milliseconds
void slow_pulse() {
  led_ring.reset();
  set_pwm_off();
  unsigned long timestamp = millis();
  if (last_slow_pulse == 0 || timestamp < last_slow_pulse) 
    last_slow_pulse = timestamp;
  if (timestamp >= last_slow_pulse + SLOW_PULSE_DELAY) {
    send_single_pulse(SLOW_PULSE_LENGTH);
    last_slow_pulse = timestamp;
  }
}

#define TEST_MODE_START_PULSE       2 // microseconds
#define TEST_MODE_PULSE_PER_STEP    4 // microseconds
#define TEST_MODE_PULSE_SPACING  2000 // milliseconds
#define TEST_MODE_PULSE_DELAY     500 // milliseconds

void test_mode() {
  // Red bar graph indicating the test mode index
  led_ring.bar_graph(test_mode_index + 1, 255, 0, 0);
  set_pwm_off();
  
  if (test_mode_pulse) {
    // Force an interval between pulses
    if (test_mode_pulse_start + TEST_MODE_PULSE_SPACING >= millis()
        && digitalRead(TRIG_IN) == LOW) {
      test_mode_pulse = false;
      test_mode_pulse_start = 0;
    }
  } else {
    if (digitalRead(MSTR_EN) == HIGH && digitalRead(TRIG_IN) == HIGH) {
      delay(TEST_MODE_DEBOUNCE);
      if (digitalRead(MSTR_EN) == HIGH && digitalRead(TRIG_IN) == HIGH) {
        delay(TEST_MODE_PULSE_DELAY - TEST_MODE_DEBOUNCE);
        if (digitalRead(MSTR_EN) == HIGH) {
          send_single_pulse(TEST_MODE_START_PULSE 
              + test_mode_index * TEST_MODE_PULSE_PER_STEP);        
          test_mode_pulse = true;
          test_mode_pulse_start = millis();
        }
      }      
    }
  }
}
