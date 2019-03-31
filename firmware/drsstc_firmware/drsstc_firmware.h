#pragma once

#include <arduino.h>          // Main Arduino header
#include "pin_definitions.h"  // Pin numbers
#include "StateMachine.h"     // Define states
#include "LEDRing.h"          // Neopixel
#include "MusicPlayer.h"      // MIDI->timers
#include <Wire.h>             // I2C (for DAC)
#include <MCP47X6.h>          // DAC
