#pragma once
#define SERIAL_LOGGING

// State machine
#define STARTUP       0  // Initial state
#define LIGHT_SHOW    1  // LEDs running but no pulses
#define SLOW_PULSE    2  // Long, slow pulses with LEDs off
#define MUSIC_PLAY    3  // Playing a song from memory
#define MUSIC_PAUSE   4  // Paused during playback
#define MUSIC_INT     5  // In between songs
#define TEST_MODE     6  // Test mode for single pulses
#define TEST_MODE_INC 7  // Increment length of pulse in test mode
#define SHUTDOWN      8  // Terminal state after a timeout (requires reset)

int get_current_state();
void change_state(int new_state);
void update_state_machine();
void flash_status();

void slow_pulse();
void test_mode();
