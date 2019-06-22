#include "MIDIPlayer.h"

// converted from beethoven_ode_to_joy.mid - 416 bytes total
extern const byte ODE_TO_JOY[] PROGMEM = 
{
      0x07,0xc0,0x1a,0x14,0x9b, //      0 BEGIN PROGRAM (960 ticks/beat, tempo = 428571 us/beat)
                0x80,0xc0,0x07, //      0 T1 ON, NOTE  64 VOLUME  7
                0x80,0x3c,0x07, //      0 T2 ON, NOTE  60 VOLUME  7
           0x07,0xd3,0x37,0x07, //    979 T2 ON, NOTE  55 VOLUME  7
           0x07,0xad,0x41,0x09, //    941 T2 ON, NOTE  65 VOLUME  9
                0x93,0xb7,0x07, //     19 T1 ON, NOTE  55 VOLUME  7
           0x07,0xad,0xc3,0x09, //    941 T1 ON, NOTE  67 VOLUME  9
                0x93,0x30,0x07, //     19 T2 ON, NOTE  48 VOLUME  7
           0x07,0xad,0xc3,0x08, //    941 T1 ON, NOTE  67 VOLUME  8
                0x80,0x37,0x08, //      0 T2 ON, NOTE  55 VOLUME  8
           0x07,0xc0,0x41,0x07, //    960 T2 ON, NOTE  65 VOLUME  7
                0x93,0xb7,0x08, //     19 T1 ON, NOTE  55 VOLUME  8
           0x07,0xad,0xc0,0x08, //    941 T1 ON, NOTE  64 VOLUME  8
                0x93,0x37,0x08, //     19 T2 ON, NOTE  55 VOLUME  8
           0x07,0xad,0x3e,0x07, //    941 T2 ON, NOTE  62 VOLUME  7
                0x93,0xb7,0x08, //     19 T1 ON, NOTE  55 VOLUME  8
           0x07,0xad,0xbc,0x07, //    941 T1 ON, NOTE  60 VOLUME  7
                0x93,0x37,0x08, //     19 T2 ON, NOTE  55 VOLUME  8
           0x07,0xad,0xbc,0x08, //    941 T1 ON, NOTE  60 VOLUME  8
           0x07,0xc0,0x3e,0x09, //    960 T2 ON, NOTE  62 VOLUME  9
                0x93,0xb7,0x08, //     19 T1 ON, NOTE  55 VOLUME  8
           0x07,0xad,0xc0,0x09, //    941 T1 ON, NOTE  64 VOLUME  9
                0x93,0x37,0x08, //     19 T2 ON, NOTE  55 VOLUME  8
           0x0b,0xa0,0x3e,0x08, //   1440 T2 ON, NOTE  62 VOLUME  8
                0x9a,0xb7,0x08, //     26 T1 ON, NOTE  55 VOLUME  8
           0x03,0xc6,0xbe,0x08, //    454 T1 ON, NOTE  62 VOLUME  8
                0x80,0x3b,0x08, //      0 T2 ON, NOTE  59 VOLUME  8
           0x0e,0x9f,0xb7,0x08, //   1823 T1 ON, NOTE  55 VOLUME  8
                     0x80,0x00, //      0 T2 OFF
                0xe1,0xc0,0x08, //     97 T1 ON, NOTE  64 VOLUME  8
                0x80,0x3c,0x08, //      0 T2 ON, NOTE  60 VOLUME  8
           0x07,0xc0,0xc0,0x09, //    960 T1 ON, NOTE  64 VOLUME  9
                0x93,0x37,0x08, //     19 T2 ON, NOTE  55 VOLUME  8
           0x07,0xad,0x41,0x08, //    941 T2 ON, NOTE  65 VOLUME  8
                0x93,0xb7,0x08, //     19 T1 ON, NOTE  55 VOLUME  8
           0x07,0xad,0xc3,0x09, //    941 T1 ON, NOTE  67 VOLUME  9
                0x93,0x30,0x08, //     19 T2 ON, NOTE  48 VOLUME  8
           0x07,0xad,0xc3,0x08, //    941 T1 ON, NOTE  67 VOLUME  8
                0x80,0x37,0x08, //      0 T2 ON, NOTE  55 VOLUME  8
           0x07,0xc0,0x41,0x08, //    960 T2 ON, NOTE  65 VOLUME  8
                0x93,0xb7,0x08, //     19 T1 ON, NOTE  55 VOLUME  8
           0x07,0xad,0xc0,0x08, //    941 T1 ON, NOTE  64 VOLUME  8
                0x93,0x37,0x08, //     19 T2 ON, NOTE  55 VOLUME  8
           0x07,0xad,0x3e,0x07, //    941 T2 ON, NOTE  62 VOLUME  7
                0x93,0xb7,0x08, //     19 T1 ON, NOTE  55 VOLUME  8
           0x07,0xad,0xbc,0x08, //    941 T1 ON, NOTE  60 VOLUME  8
                0x93,0x37,0x08, //     19 T2 ON, NOTE  55 VOLUME  8
           0x0e,0xed,0x3e,0x09, //   1901 T2 ON, NOTE  62 VOLUME  9
                0x93,0xb7,0x08, //     19 T1 ON, NOTE  55 VOLUME  8
           0x07,0xad,0xc0,0x09, //    941 T1 ON, NOTE  64 VOLUME  9
                0x93,0x37,0x08, //     19 T2 ON, NOTE  55 VOLUME  8
           0x07,0xad,0x3e,0x08, //    941 T2 ON, NOTE  62 VOLUME  8
                0x93,0xb7,0x08, //     19 T1 ON, NOTE  55 VOLUME  8
           0x0b,0x8d,0xbc,0x08, //   1421 T1 ON, NOTE  60 VOLUME  8
                0x9a,0x37,0x08, //     26 T2 ON, NOTE  55 VOLUME  8
           0x03,0xc6,0x30,0x08, //    454 T2 ON, NOTE  48 VOLUME  8
                0x0e,0x9f,0x80, //   1823 T1 OFF
                0xe1,0xbe,0x06, //     97 T1 ON, NOTE  62 VOLUME  6
                0x80,0x37,0x05, //      0 T2 ON, NOTE  55 VOLUME  5
           0x07,0xc0,0xbe,0x05, //    960 T1 ON, NOTE  62 VOLUME  5
           0x07,0xc0,0x40,0x06, //    960 T2 ON, NOTE  64 VOLUME  6
                0x93,0xb7,0x05, //     19 T1 ON, NOTE  55 VOLUME  5
           0x07,0xad,0xbc,0x05, //    941 T1 ON, NOTE  60 VOLUME  5
                0x93,0x37,0x05, //     19 T2 ON, NOTE  55 VOLUME  5
           0x07,0xad,0x3e,0x05, //    941 T2 ON, NOTE  62 VOLUME  5
                0x93,0xb7,0x05, //     19 T1 ON, NOTE  55 VOLUME  5
           0x07,0xad,0xc0,0x06, //    941 T1 ON, NOTE  64 VOLUME  6
                0x93,0x37,0x05, //     19 T2 ON, NOTE  55 VOLUME  5
           0x03,0xcd,0x41,0x05, //    461 T2 ON, NOTE  65 VOLUME  5
                0x88,0xb7,0x05, //      8 T1 ON, NOTE  55 VOLUME  5
           0x03,0xd8,0xc0,0x05, //    472 T1 ON, NOTE  64 VOLUME  5
                0x88,0x37,0x05, //      8 T2 ON, NOTE  55 VOLUME  5
           0x07,0xb8,0x3c,0x04, //    952 T2 ON, NOTE  60 VOLUME  4
                0x93,0xb7,0x05, //     19 T1 ON, NOTE  55 VOLUME  5
           0x07,0xad,0xbe,0x06, //    941 T1 ON, NOTE  62 VOLUME  6
                0x93,0x37,0x05, //     19 T2 ON, NOTE  55 VOLUME  5
           0x07,0xad,0x40,0x06, //    941 T2 ON, NOTE  64 VOLUME  6
                0x93,0xb7,0x05, //     19 T1 ON, NOTE  55 VOLUME  5
           0x03,0xcd,0xc1,0x06, //    461 T1 ON, NOTE  65 VOLUME  6
                0x88,0x37,0x05, //      8 T2 ON, NOTE  55 VOLUME  5
           0x03,0xd8,0x40,0x05, //    472 T2 ON, NOTE  64 VOLUME  5
                0x88,0xb8,0x05, //      8 T1 ON, NOTE  56 VOLUME  5
           0x07,0xb8,0xbe,0x05, //    952 T1 ON, NOTE  62 VOLUME  5
                0x93,0x38,0x05, //     19 T2 ON, NOTE  56 VOLUME  5
           0x07,0xad,0x3c,0x05, //    941 T2 ON, NOTE  60 VOLUME  5
                0x93,0xb9,0x05, //     19 T1 ON, NOTE  57 VOLUME  5
           0x07,0xad,0xbe,0x05, //    941 T1 ON, NOTE  62 VOLUME  5
                0x93,0x36,0x05, //     19 T2 ON, NOTE  54 VOLUME  5
                0x06,0xfc,0x80, //    892 T1 OFF
                0xb1,0xb7,0x05, //     49 T1 ON, NOTE  55 VOLUME  5
                     0x80,0x00, //      0 T2 OFF
           0x07,0xc0,0x40,0x07, //    960 T2 ON, NOTE  64 VOLUME  7
           0x07,0xc0,0xbc,0x09, //    960 T1 ON, NOTE  60 VOLUME  9
           0x07,0xc0,0x40,0x08, //    960 T2 ON, NOTE  64 VOLUME  8
           0x07,0xc0,0xc1,0x08, //    960 T1 ON, NOTE  65 VOLUME  8
                0x93,0x3a,0x08, //     19 T2 ON, NOTE  58 VOLUME  8
           0x07,0xad,0x43,0x09, //    941 T2 ON, NOTE  67 VOLUME  9
                0x93,0xba,0x08, //     19 T1 ON, NOTE  58 VOLUME  8
           0x07,0xad,0xc3,0x08, //    941 T1 ON, NOTE  67 VOLUME  8
                0x80,0x39,0x08, //      0 T2 ON, NOTE  57 VOLUME  8
           0x07,0xc0,0x41,0x07, //    960 T2 ON, NOTE  65 VOLUME  7
                0x93,0xb9,0x08, //     19 T1 ON, NOTE  57 VOLUME  8
           0x07,0xad,0xc0,0x08, //    941 T1 ON, NOTE  64 VOLUME  8
                0x93,0x35,0x08, //     19 T2 ON, NOTE  53 VOLUME  8
           0x07,0xad,0x3e,0x08, //    941 T2 ON, NOTE  62 VOLUME  8
                0x93,0xb5,0x08, //     19 T1 ON, NOTE  53 VOLUME  8
           0x07,0xad,0xbc,0x08, //    941 T1 ON, NOTE  60 VOLUME  8
                0x93,0x34,0x08, //     19 T2 ON, NOTE  52 VOLUME  8
           0x0e,0xed,0x3e,0x08, //   1901 T2 ON, NOTE  62 VOLUME  8
                0x93,0xb7,0x08, //     19 T1 ON, NOTE  55 VOLUME  8
           0x07,0xad,0xc0,0x09, //    941 T1 ON, NOTE  64 VOLUME  9
                0x93,0x3c,0x09, //     19 T2 ON, NOTE  60 VOLUME  9
           0x07,0xad,0x3e,0x08, //    941 T2 ON, NOTE  62 VOLUME  8
                0x93,0xb7,0x08, //     19 T1 ON, NOTE  55 VOLUME  8
           0x0b,0x8d,0xbc,0x07, //   1421 T1 ON, NOTE  60 VOLUME  7
                0x9a,0x37,0x08, //     26 T2 ON, NOTE  55 VOLUME  8
           0x03,0xc6,0xbc,0x08, //    454 T1 ON, NOTE  60 VOLUME  8
           0x0e,0x9f,0xb4,0x08, //   1823 T1 ON, NOTE  52 VOLUME  8
                     0xe1,0x01, //     97 BOTH OFF
                     0x80,0x05  //      0 END PROGRAM
};
