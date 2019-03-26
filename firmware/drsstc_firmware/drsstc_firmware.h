#pragma once

#include <arduino.h>
#include "TimeSignature.h"
#include "LEDRing.h"
#include "MusicPlayer.h"
#include <Wire.h>

#include <MCP47X6.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
