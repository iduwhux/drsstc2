#include "drsstc_firmware.h"

// Setup DAC
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

  #ifdef SERIAL_LOGGING
  Serial.begin(9600);
  Serial.println(F("DRSSTC Firmware v1.0 - written by Brian Boucher, June 2019"));
  #endif

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
  #ifdef SERIAL_LOGGING
  Serial.print(F("Initialized DAC at "));
  Serial.println(INITIAL_DAC_VALUE);
  #endif

  // Initialize timer1/timer2 outputs for interrupter
  setup_timers();

  init_led_strip();
}

void loop() {
  update_state_machine();
  switch (get_current_state()) {
    case STARTUP:
      led_strip_flash();
      break;
    case LIGHT_SHOW: 
    case MUSIC_INT:
      led_strip_cycle();
      break;
    case SLOW_PULSE: 
      slow_pulse();
      break;
    case MUSIC_PLAY:
      if (!play_midi()) change_state(MUSIC_INT);
      break;
    case TEST_MODE: 
      test_mode(); 
      break;
  }
}
