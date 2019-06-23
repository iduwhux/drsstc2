#include "drsstc_firmware.h"

// Setup DAC
#define DAC_ADDRESS       0x60
const uint8_t INITIAL_DAC_VALUE = 0x80;
MCP47X6 DAC = MCP47X6(DAC_ADDRESS);

unsigned long ocd_count = 0;
void ocd_int() { ocd_count++; }

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

  // Set OCD interrupt
  attachInterrupt(digitalPinToInterrupt(OCD_DETECT), ocd_int, RISING);

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

#ifdef SERIAL_LOGGING
  #define SERIAL_HEARTBEAT_TIME 5000
  unsigned long last_serial_heartbeat = 0;
#endif

void loop() {
  update_state_machine();
  led_update();
  switch (get_current_state()) {
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

  #ifdef SERIAL_LOGGING
  unsigned long timestamp = millis();
  if (last_serial_heartbeat == 0 || last_serial_heartbeat > timestamp)
    last_serial_heartbeat = timestamp;
  if (timestamp > last_serial_heartbeat + SERIAL_HEARTBEAT_TIME) {
    Serial.print(F("Heartbeat: "));
    Serial.print(ocd_count);
    Serial.print(F(" OCD, "));
    Serial.print(midi_instruction_count);
    Serial.println(F(" MIDI"));
  }
  #endif
}
