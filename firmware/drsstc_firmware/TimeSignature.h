#pragma once
typedef unsigned long time_t;


#include <stdint.h>
typedef struct __attribute__((packed)) {
  bool flash   : 1;
  bool fade    : 1;
  bool solid   : 1;
  byte segment : 5;
  bool disable : 1;
  time_t time_ms : 11; // 0 - 2047 ms for flash/fade/rotate periods
  union {
    struct {
      bool apply_to_individual : 1;
      bool apply_to_quad       : 1;
      bool apply_to_even_odd   : 1;
      bool set_start           : 1; // Use start_idx values
      byte start_idx           : 4; // Initial LED 0-15
      byte step_size           : 4; // Step size 0-15
    };
    struct {
      byte red     : 4;
      byte green   : 4;
      byte blue    : 4;
    };
  };
} LEDInstruction;  // 32-bit
