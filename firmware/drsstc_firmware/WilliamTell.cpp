#include "MIDIPlayer.h"

extern const byte WILLIAM_TELL[] PROGMEM  =
{     0x80,0x02,0x16,0x71,0xd8, //     0 TEMPO > 375000
                0x80,0x3e,0x08, //     0 T2 ON, NOTE 62 VOLUME 8
           0x16,0xc0,0x3e,0x09, //  2880 T2 ON, NOTE 62 VOLUME 9
           0x07,0xc0,0x3e,0x0a, //   960 T2 ON, NOTE 62 VOLUME 10
           0x1e,0x80,0x3e,0x09, //  3840 T2 ON, NOTE 62 VOLUME 9
           0x07,0xc0,0x3b,0x08, //   960 T2 ON, NOTE 59 VOLUME 8
           0x07,0xc0,0x37,0x08, //   960 T2 ON, NOTE 55 VOLUME 8
           0x07,0xc0,0x3b,0x0a, //   960 T2 ON, NOTE 59 VOLUME 10
           0x07,0xc0,0x3e,0x08, //   960 T2 ON, NOTE 62 VOLUME 8
           0x07,0xc0,0x3b,0x08, //   960 T2 ON, NOTE 59 VOLUME 8
           0x07,0xc0,0x3e,0x08, //   960 T2 ON, NOTE 62 VOLUME 8
           0x07,0xc0,0x43,0x0b, //   960 T2 ON, NOTE 67 VOLUME 11
           0x07,0xc0,0x32,0x08, //   960 T2 ON, NOTE 50 VOLUME 8
                0x80,0xbe,0x08, //     0 T1 ON, NOTE 62 VOLUME 8
           0x16,0xc0,0x32,0x09, //  2880 T2 ON, NOTE 50 VOLUME 9
                0x80,0xbe,0x09, //     0 T1 ON, NOTE 62 VOLUME 9
           0x03,0xe0,0x32,0x0a, //   480 T2 ON, NOTE 50 VOLUME 10
           0x03,0xe0,0x32,0x09, //   480 T2 ON, NOTE 50 VOLUME 9
           0x16,0xc0,0xbe,0x0a, //  2880 T1 ON, NOTE 62 VOLUME 10
           0x03,0xe0,0xbe,0x09, //   480 T1 ON, NOTE 62 VOLUME 9
           0x03,0xe0,0x39,0x0a, //   480 T2 ON, NOTE 57 VOLUME 10
           0x21,0xe0,0x3e,0x09, //  4320 T2 ON, NOTE 62 VOLUME 9
                     0x80,0x80, //     0 T1 OFF
           0x03,0xe0,0x3e,0x0a, //   480 T2 ON, NOTE 62 VOLUME 10
           0x03,0xe0,0x3b,0x08, //   480 T2 ON, NOTE 59 VOLUME 8
                0x80,0xbe,0x0a, //     0 T1 ON, NOTE 62 VOLUME 10
           0x07,0xc0,0x3e,0x09, //   960 T2 ON, NOTE 62 VOLUME 9
                     0x80,0x80, //     0 T1 OFF
           0x07,0xc0,0x3b,0x08, //   960 T2 ON, NOTE 59 VOLUME 8
                0x80,0xbe,0x09, //     0 T1 ON, NOTE 62 VOLUME 9
           0x07,0xc0,0x3e,0x09, //   960 T2 ON, NOTE 62 VOLUME 9
                     0x80,0x80, //     0 T1 OFF
           0x07,0xc0,0x3b,0x09, //   960 T2 ON, NOTE 59 VOLUME 9
                0x80,0xc3,0x0b, //     0 T1 ON, NOTE 67 VOLUME 11
           0x07,0xc0,0x43,0x0b, //   960 T2 ON, NOTE 67 VOLUME 11
                0x80,0xc5,0x0c, //     0 T1 ON, NOTE 69 VOLUME 12
                0x93,0x39,0x08, //    19 T2 ON, NOTE 57 VOLUME 8
           0x07,0xad,0x45,0x0c, //   941 T2 ON, NOTE 69 VOLUME 12
                0x80,0xc7,0x0a, //     0 T1 ON, NOTE 71 VOLUME 10
                0x93,0x37,0x0a, //    19 T2 ON, NOTE 55 VOLUME 10
                0x06,0xfc,0x01, //   892 BOTH OFF
                0xb1,0x3e,0x07, //    49 T2 ON, NOTE 62 VOLUME 7
           0x03,0xe0,0x3e,0x09, //   480 T2 ON, NOTE 62 VOLUME 9
           0x03,0xe0,0x3b,0x08, //   480 T2 ON, NOTE 59 VOLUME 8
                0x80,0xbe,0x09, //     0 T1 ON, NOTE 62 VOLUME 9
           0x07,0xc0,0x3e,0x09, //   960 T2 ON, NOTE 62 VOLUME 9
                     0x80,0x80, //     0 T1 OFF
           0x07,0xc0,0x3b,0x09, //   960 T2 ON, NOTE 59 VOLUME 9
                0x80,0xc3,0x0b, //     0 T1 ON, NOTE 67 VOLUME 11
           0x07,0xc0,0x47,0x0b, //   960 T2 ON, NOTE 71 VOLUME 11
                     0x80,0x80, //     0 T1 OFF
           0x07,0xc0,0x32,0x08, //   960 T2 ON, NOTE 50 VOLUME 8
                0x80,0xc5,0x09, //     0 T1 ON, NOTE 69 VOLUME 9
           0x07,0xc0,0x42,0x08, //   960 T2 ON, NOTE 66 VOLUME 8
                0x93,0x32,0x08, //    19 T2 ON, NOTE 50 VOLUME 8
                0x80,0xc2,0x08, //     0 T1 ON, NOTE 66 VOLUME 8
           0x07,0xad,0x3e,0x08, //   941 T2 ON, NOTE 62 VOLUME 8
                0x93,0x32,0x09, //    19 T2 ON, NOTE 50 VOLUME 9
                0x80,0xbe,0x08, //     0 T1 ON, NOTE 62 VOLUME 8
                0x06,0xfc,0x80, //   892 T1 OFF
                0xb1,0x3e,0x09, //    49 T2 ON, NOTE 62 VOLUME 9
           0x03,0xe0,0x3e,0x0a, //   480 T2 ON, NOTE 62 VOLUME 10
           0x03,0xe0,0x3b,0x08, //   480 T2 ON, NOTE 59 VOLUME 8
                0x80,0xbe,0x0a, //     0 T1 ON, NOTE 62 VOLUME 10
           0x07,0xc0,0x3e,0x09, //   960 T2 ON, NOTE 62 VOLUME 9
                     0x80,0x80, //     0 T1 OFF
           0x07,0xc0,0x3b,0x08, //   960 T2 ON, NOTE 59 VOLUME 8
                0x80,0xbe,0x0a, //     0 T1 ON, NOTE 62 VOLUME 10
           0x07,0xc0,0x3e,0x09, //   960 T2 ON, NOTE 62 VOLUME 9
                     0x80,0x80, //     0 T1 OFF
           0x03,0xe0,0x3e,0x0a, //   480 T2 ON, NOTE 62 VOLUME 10
           0x03,0xe0,0x3b,0x08, //   480 T2 ON, NOTE 59 VOLUME 8
                0x80,0xc3,0x0b, //     0 T1 ON, NOTE 67 VOLUME 11
           0x07,0xc0,0x39,0x09, //   960 T2 ON, NOTE 57 VOLUME 9
                0x80,0xc5,0x0a, //     0 T1 ON, NOTE 69 VOLUME 10
           0x07,0xc0,0x37,0x09, //   960 T2 ON, NOTE 55 VOLUME 9
                0x80,0xc7,0x0a, //     0 T1 ON, NOTE 71 VOLUME 10
           0x07,0xc0,0x43,0x08, //   960 T2 ON, NOTE 67 VOLUME 8
                     0x80,0x80, //     0 T1 OFF
           0x03,0xe0,0xc7,0x0b, //   480 T1 ON, NOTE 71 VOLUME 11
                0x88,0x47,0x0b, //     8 T2 ON, NOTE 71 VOLUME 11
                     0x80,0x80, //     0 T1 OFF
           0x03,0xd8,0xca,0x0c, //   472 T1 ON, NOTE 74 VOLUME 12
                0x88,0x32,0x0a, //     8 T2 ON, NOTE 50 VOLUME 10
           0x12,0xd8,0x48,0x0b, //  2392 T2 ON, NOTE 72 VOLUME 11
                0xad,0x32,0x0a, //    45 T2 ON, NOTE 50 VOLUME 10
                0x80,0xc8,0x0b, //     0 T1 ON, NOTE 72 VOLUME 11
           0x03,0xb3,0x47,0x0b, //   435 T2 ON, NOTE 71 VOLUME 11
                0x88,0x32,0x0a, //     8 T2 ON, NOTE 50 VOLUME 10
                0x80,0xc7,0x0b, //     0 T1 ON, NOTE 71 VOLUME 11
           0x03,0xd8,0x45,0x0a, //   472 T2 ON, NOTE 69 VOLUME 10
                0x88,0x32,0x0a, //     8 T2 ON, NOTE 50 VOLUME 10
                0x80,0xc5,0x0a, //     0 T1 ON, NOTE 69 VOLUME 10
           0x03,0xd8,0x43,0x0c, //   472 T2 ON, NOTE 67 VOLUME 12
                0x88,0x37,0x0c, //     8 T2 ON, NOTE 55 VOLUME 12
                0x80,0xc3,0x0c, //     0 T1 ON, NOTE 67 VOLUME 12
                0x07,0x87,0x80, //   903 T1 OFF
                0xb1,0x32,0x0c, //    49 T2 ON, NOTE 50 VOLUME 12
                0x80,0xc7,0x0c, //     0 T1 ON, NOTE 71 VOLUME 12
           0x07,0xc0,0x37,0x0c, //   960 T2 ON, NOTE 55 VOLUME 12
                0x80,0xc3,0x0c, //     0 T1 ON, NOTE 67 VOLUME 12
           0x07,0xc0,0x3e,0x09, //   960 T2 ON, NOTE 62 VOLUME 9
                     0x80,0x80, //     0 T1 OFF
           0x03,0xe0,0x3e,0x0b, //   480 T2 ON, NOTE 62 VOLUME 11
           0x03,0xe0,0x3b,0x0a, //   480 T2 ON, NOTE 59 VOLUME 10
                0x80,0xbe,0x0b, //     0 T1 ON, NOTE 62 VOLUME 11
           0x07,0xc0,0x3e,0x0b, //   960 T2 ON, NOTE 62 VOLUME 11
                     0x80,0x80, //     0 T1 OFF
           0x07,0xc0,0x3b,0x09, //   960 T2 ON, NOTE 59 VOLUME 9
                0x80,0xbe,0x0b, //     0 T1 ON, NOTE 62 VOLUME 11
           0x07,0xc0,0x3e,0x0b, //   960 T2 ON, NOTE 62 VOLUME 11
                     0x80,0x80, //     0 T1 OFF
           0x07,0xc0,0x3b,0x0a, //   960 T2 ON, NOTE 59 VOLUME 10
                0x80,0xc3,0x0c, //     0 T1 ON, NOTE 67 VOLUME 12
           0x07,0xc0,0x43,0x0c, //   960 T2 ON, NOTE 67 VOLUME 12
                0x80,0xc5,0x0c, //     0 T1 ON, NOTE 69 VOLUME 12
                0x93,0x39,0x09, //    19 T2 ON, NOTE 57 VOLUME 9
           0x07,0xad,0x45,0x0c, //   941 T2 ON, NOTE 69 VOLUME 12
                0x80,0xc7,0x0c, //     0 T1 ON, NOTE 71 VOLUME 12
                0x93,0x37,0x0b, //    19 T2 ON, NOTE 55 VOLUME 11
                0x06,0xfc,0x01, //   892 BOTH OFF
                0xb1,0x3e,0x08, //    49 T2 ON, NOTE 62 VOLUME 8
           0x03,0xe0,0x3e,0x0a, //   480 T2 ON, NOTE 62 VOLUME 10
           0x03,0xe0,0x3b,0x0a, //   480 T2 ON, NOTE 59 VOLUME 10
                0x80,0xbe,0x0b, //     0 T1 ON, NOTE 62 VOLUME 11
           0x07,0xc0,0x3e,0x0b, //   960 T2 ON, NOTE 62 VOLUME 11
                     0x80,0x80, //     0 T1 OFF
           0x07,0xc0,0x3b,0x0a, //   960 T2 ON, NOTE 59 VOLUME 10
                0x80,0xc3,0x0c, //     0 T1 ON, NOTE 67 VOLUME 12
           0x07,0xc0,0x47,0x0c, //   960 T2 ON, NOTE 71 VOLUME 12
                     0x80,0x80, //     0 T1 OFF
           0x07,0xc0,0x32,0x0a, //   960 T2 ON, NOTE 50 VOLUME 10
                0x80,0xc5,0x0b, //     0 T1 ON, NOTE 69 VOLUME 11
           0x07,0xc0,0x42,0x0a, //   960 T2 ON, NOTE 66 VOLUME 10
                0x93,0x32,0x0a, //    19 T2 ON, NOTE 50 VOLUME 10
                0x80,0xc2,0x0a, //     0 T1 ON, NOTE 66 VOLUME 10
           0x07,0xad,0x3e,0x0a, //   941 T2 ON, NOTE 62 VOLUME 10
                0x93,0x32,0x0b, //    19 T2 ON, NOTE 50 VOLUME 11
                0x80,0xbe,0x0a, //     0 T1 ON, NOTE 62 VOLUME 10
                0x06,0xfc,0x80, //   892 T1 OFF
                0xb1,0x3e,0x0a, //    49 T2 ON, NOTE 62 VOLUME 10
           0x03,0xe0,0x3e,0x0b, //   480 T2 ON, NOTE 62 VOLUME 11
           0x03,0xe0,0x3b,0x0a, //   480 T2 ON, NOTE 59 VOLUME 10
                0x80,0xbe,0x0b, //     0 T1 ON, NOTE 62 VOLUME 11
           0x07,0xc0,0x3e,0x0b, //   960 T2 ON, NOTE 62 VOLUME 11
                     0x80,0x80, //     0 T1 OFF
           0x07,0xc0,0x3b,0x0a, //   960 T2 ON, NOTE 59 VOLUME 10
                0x80,0xbe,0x0b, //     0 T1 ON, NOTE 62 VOLUME 11
           0x07,0xc0,0x3e,0x0b, //   960 T2 ON, NOTE 62 VOLUME 11
                     0x80,0x80, //     0 T1 OFF
           0x07,0xc0,0x3b,0x0a, //   960 T2 ON, NOTE 59 VOLUME 10
                0x80,0xc3,0x0c, //     0 T1 ON, NOTE 67 VOLUME 12
           0x07,0xc0,0x39,0x0b, //   960 T2 ON, NOTE 57 VOLUME 11
                0x80,0xc5,0x0c, //     0 T1 ON, NOTE 69 VOLUME 12
           0x07,0xc0,0x37,0x0a, //   960 T2 ON, NOTE 55 VOLUME 10
                0x80,0xc7,0x0b, //     0 T1 ON, NOTE 71 VOLUME 11
           0x07,0xc0,0x43,0x0a, //   960 T2 ON, NOTE 67 VOLUME 10
                     0x80,0x80, //     0 T1 OFF
           0x03,0xe0,0xc7,0x0c, //   480 T1 ON, NOTE 71 VOLUME 12
                0x88,0x47,0x0c, //     8 T2 ON, NOTE 71 VOLUME 12
                     0x80,0x80, //     0 T1 OFF
           0x03,0xd8,0xca,0x0c, //   472 T1 ON, NOTE 74 VOLUME 12
                0x88,0x32,0x0b, //     8 T2 ON, NOTE 50 VOLUME 11
           0x0e,0xf8,0x32,0x0c, //  1912 T2 ON, NOTE 50 VOLUME 12
           0x03,0xe0,0x48,0x0c, //   480 T2 ON, NOTE 72 VOLUME 12
                0xad,0x32,0x0c, //    45 T2 ON, NOTE 50 VOLUME 12
                0x80,0xc8,0x0c, //     0 T1 ON, NOTE 72 VOLUME 12
           0x03,0xb3,0x47,0x0b, //   435 T2 ON, NOTE 71 VOLUME 11
                0x88,0x32,0x0c, //     8 T2 ON, NOTE 50 VOLUME 12
                0x80,0xc7,0x0b, //     0 T1 ON, NOTE 71 VOLUME 11
           0x03,0xd8,0x45,0x0b, //   472 T2 ON, NOTE 69 VOLUME 11
                0x88,0x32,0x0c, //     8 T2 ON, NOTE 50 VOLUME 12
                0x80,0xc5,0x0b, //     0 T1 ON, NOTE 69 VOLUME 11
           0x03,0xd8,0x43,0x0c, //   472 T2 ON, NOTE 67 VOLUME 12
                0x88,0x37,0x0c, //     8 T2 ON, NOTE 55 VOLUME 12
                0x80,0xc3,0x0c, //     0 T1 ON, NOTE 67 VOLUME 12
                0x07,0x87,0x80, //   903 T1 OFF
                0xb1,0x32,0x0c, //    49 T2 ON, NOTE 50 VOLUME 12
                0x80,0xc7,0x0c, //     0 T1 ON, NOTE 71 VOLUME 12
           0x07,0xc0,0x37,0x0c, //   960 T2 ON, NOTE 55 VOLUME 12
                0x80,0xc3,0x0c, //     0 T1 ON, NOTE 67 VOLUME 12
           0x07,0xc0,0x47,0x06, //   960 T2 ON, NOTE 71 VOLUME 6
                     0x80,0x80, //     0 T1 OFF
           0x07,0xc0,0x3b,0x05, //   960 T2 ON, NOTE 59 VOLUME 5
                0x80,0xc7,0x06, //     0 T1 ON, NOTE 71 VOLUME 6
           0x07,0xc0,0x47,0x06, //   960 T2 ON, NOTE 71 VOLUME 6
                     0x80,0x80, //     0 T1 OFF
           0x07,0xc0,0x3b,0x05, //   960 T2 ON, NOTE 59 VOLUME 5
                0x80,0xc7,0x06, //     0 T1 ON, NOTE 71 VOLUME 6
           0x07,0xc0,0x47,0x06, //   960 T2 ON, NOTE 71 VOLUME 6
                     0x80,0x80, //     0 T1 OFF
           0x07,0xc0,0x3b,0x05, //   960 T2 ON, NOTE 59 VOLUME 5
                0x80,0xc7,0x06, //     0 T1 ON, NOTE 71 VOLUME 6
           0x07,0xc0,0x4c,0x06, //   960 T2 ON, NOTE 76 VOLUME 6
                     0x80,0x80, //     0 T1 OFF
           0x07,0xc0,0x3b,0x05, //   960 T2 ON, NOTE 59 VOLUME 5
                0x80,0xc7,0x05, //     0 T1 ON, NOTE 71 VOLUME 5
           0x07,0xc0,0x4c,0x06, //   960 T2 ON, NOTE 76 VOLUME 6
                     0x80,0x80, //     0 T1 OFF
           0x07,0xc0,0x3b,0x05, //   960 T2 ON, NOTE 59 VOLUME 5
                0x80,0xc7,0x05, //     0 T1 ON, NOTE 71 VOLUME 5
           0x07,0xc0,0x47,0x05, //   960 T2 ON, NOTE 71 VOLUME 5
                0x80,0xcc,0x05, //     0 T1 ON, NOTE 76 VOLUME 5
                0x93,0x4c,0x05, //    19 T2 ON, NOTE 76 VOLUME 5
                     0x80,0x80, //     0 T1 OFF
           0x07,0xad,0x47,0x05, //   941 T2 ON, NOTE 71 VOLUME 5
                0x80,0xcc,0x05, //     0 T1 ON, NOTE 76 VOLUME 5
                0x93,0x3b,0x05, //    19 T2 ON, NOTE 59 VOLUME 5
                0x80,0xc7,0x05, //     0 T1 ON, NOTE 71 VOLUME 5
           0x07,0xad,0x45,0x04, //   941 T2 ON, NOTE 69 VOLUME 4
                     0x93,0x80, //    19 T1 OFF
           0x07,0xad,0x43,0x05, //   941 T2 ON, NOTE 67 VOLUME 5
                0x80,0xc5,0x04, //     0 T1 ON, NOTE 69 VOLUME 4
                0x93,0x3b,0x05, //    19 T2 ON, NOTE 59 VOLUME 5
                0x80,0xc3,0x05, //     0 T1 ON, NOTE 67 VOLUME 5
           0x07,0xad,0x42,0x05, //   941 T2 ON, NOTE 66 VOLUME 5
                0x93,0x39,0x05, //    19 T2 ON, NOTE 57 VOLUME 5
                0x80,0xc2,0x05, //     0 T1 ON, NOTE 66 VOLUME 5
           0x07,0xad,0x40,0x06, //   941 T2 ON, NOTE 64 VOLUME 6
                0x93,0x37,0x06, //    19 T2 ON, NOTE 55 VOLUME 6
                0x80,0xc0,0x06, //     0 T1 ON, NOTE 64 VOLUME 6
                0x06,0xfc,0x80, //   892 T1 OFF
                0xb1,0x47,0x07, //    49 T2 ON, NOTE 71 VOLUME 7
           0x03,0xe0,0x47,0x06, //   480 T2 ON, NOTE 71 VOLUME 6
           0x03,0xe0,0x3b,0x05, //   480 T2 ON, NOTE 59 VOLUME 5
                0x80,0xc7,0x05, //     0 T1 ON, NOTE 71 VOLUME 5
           0x07,0xc0,0x47,0x05, //   960 T2 ON, NOTE 71 VOLUME 5
                     0x80,0x80, //     0 T1 OFF
           0x03,0xe0,0x47,0x06, //   480 T2 ON, NOTE 71 VOLUME 6
           0x03,0xe0,0x3b,0x05, //   480 T2 ON, NOTE 59 VOLUME 5
                0x80,0xc7,0x05, //     0 T1 ON, NOTE 71 VOLUME 5
           0x07,0xc0,0x47,0x06, //   960 T2 ON, NOTE 71 VOLUME 6
                     0x80,0x80, //     0 T1 OFF
           0x07,0xc0,0x3b,0x05, //   960 T2 ON, NOTE 59 VOLUME 5
                0x80,0xc7,0x06, //     0 T1 ON, NOTE 71 VOLUME 6
           0x07,0xc0,0x47,0x06, //   960 T2 ON, NOTE 71 VOLUME 6
                0x80,0xcc,0x07, //     0 T1 ON, NOTE 76 VOLUME 7
                0x93,0x4c,0x07, //    19 T2 ON, NOTE 76 VOLUME 7
                     0x80,0x80, //     0 T1 OFF
           0x07,0xad,0x47,0x06, //   941 T2 ON, NOTE 71 VOLUME 6
                0x80,0xcc,0x07, //     0 T1 ON, NOTE 76 VOLUME 7
                0x93,0x3b,0x06, //    19 T2 ON, NOTE 59 VOLUME 6
                0x80,0xc7,0x06, //     0 T1 ON, NOTE 71 VOLUME 6
           0x07,0xad,0x47,0x06, //   941 T2 ON, NOTE 71 VOLUME 6
                0x80,0xcc,0x08, //     0 T1 ON, NOTE 76 VOLUME 8
                0x93,0x4c,0x08, //    19 T2 ON, NOTE 76 VOLUME 8
                     0x80,0x80, //     0 T1 OFF
           0x07,0xad,0x47,0x07, //   941 T2 ON, NOTE 71 VOLUME 7
                0x80,0xcc,0x08, //     0 T1 ON, NOTE 76 VOLUME 8
                0x93,0x3b,0x07, //    19 T2 ON, NOTE 59 VOLUME 7
                0x80,0xc7,0x07, //     0 T1 ON, NOTE 71 VOLUME 7
           0x07,0xad,0x47,0x07, //   941 T2 ON, NOTE 71 VOLUME 7
                0x80,0xcc,0x09, //     0 T1 ON, NOTE 76 VOLUME 9
                0x93,0x4c,0x09, //    19 T2 ON, NOTE 76 VOLUME 9
                     0x80,0x80, //     0 T1 OFF
           0x07,0xad,0x4a,0x07, //   941 T2 ON, NOTE 74 VOLUME 7
                0x80,0xcc,0x09, //     0 T1 ON, NOTE 76 VOLUME 9
                0x93,0x39,0x07, //    19 T2 ON, NOTE 57 VOLUME 7
                0x80,0xca,0x07, //     0 T1 ON, NOTE 74 VOLUME 7
           0x07,0xad,0x49,0x08, //   941 T2 ON, NOTE 73 VOLUME 8
                     0x93,0x80, //    19 T1 OFF
           0x07,0xad,0xca,0x09, //   941 T1 ON, NOTE 74 VOLUME 9
                0x93,0x32,0x08, //    19 T2 ON, NOTE 50 VOLUME 8
           0x07,0xad,0x49,0x09, //   941 T2 ON, NOTE 73 VOLUME 9
                0x93,0x32,0x08, //    19 T2 ON, NOTE 50 VOLUME 8
                0x80,0xc9,0x09, //     0 T1 ON, NOTE 73 VOLUME 9
           0x07,0xad,0x49,0x09, //   941 T2 ON, NOTE 73 VOLUME 9
                0x80,0xca,0x09, //     0 T1 ON, NOTE 74 VOLUME 9
                0x93,0x32,0x08, //    19 T2 ON, NOTE 50 VOLUME 8
                0x06,0xfc,0x80, //   892 T1 OFF
                0xb1,0xbe,0x07, //    49 T1 ON, NOTE 62 VOLUME 7
           0x03,0xe0,0xbe,0x09, //   480 T1 ON, NOTE 62 VOLUME 9
           0x03,0xe0,0x2b,0x08, //   480 T2 ON, NOTE 43 VOLUME 8
           0x07,0xc0,0x3e,0x09, //   960 T2 ON, NOTE 62 VOLUME 9
                     0x80,0x80, //     0 T1 OFF
           0x03,0xe0,0x3e,0x0a, //   480 T2 ON, NOTE 62 VOLUME 10
           0x03,0xe0,0x32,0x09, //   480 T2 ON, NOTE 50 VOLUME 9
                0x80,0xbe,0x0a, //     0 T1 ON, NOTE 62 VOLUME 10
           0x07,0xc0,0x3e,0x0a, //   960 T2 ON, NOTE 62 VOLUME 10
                     0x80,0x80, //     0 T1 OFF
           0x03,0xe0,0x3e,0x09, //   480 T2 ON, NOTE 62 VOLUME 9
           0x03,0xe0,0x2f,0x08, //   480 T2 ON, NOTE 47 VOLUME 8
                0x80,0xc3,0x0b, //     0 T1 ON, NOTE 67 VOLUME 11
           0x07,0xc0,0x43,0x0b, //   960 T2 ON, NOTE 67 VOLUME 11
                0x80,0xc5,0x0c, //     0 T1 ON, NOTE 69 VOLUME 12
                0x93,0x2d,0x08, //    19 T2 ON, NOTE 45 VOLUME 8
           0x07,0xad,0x45,0x0c, //   941 T2 ON, NOTE 69 VOLUME 12
                0x80,0xc7,0x0a, //     0 T1 ON, NOTE 71 VOLUME 10
                0x93,0x2b,0x09, //    19 T2 ON, NOTE 43 VOLUME 9
                0x06,0xfc,0x01, //   892 BOTH OFF
                0xb1,0x3e,0x07, //    49 T2 ON, NOTE 62 VOLUME 7
           0x03,0xe0,0x3e,0x09, //   480 T2 ON, NOTE 62 VOLUME 9
           0x03,0xe0,0x2b,0x09, //   480 T2 ON, NOTE 43 VOLUME 9
                0x80,0xbe,0x09, //     0 T1 ON, NOTE 62 VOLUME 9
           0x07,0xc0,0x3e,0x09, //   960 T2 ON, NOTE 62 VOLUME 9
                     0x80,0x80, //     0 T1 OFF
           0x07,0xc0,0x32,0x09, //   960 T2 ON, NOTE 50 VOLUME 9
                0x80,0xc3,0x0b, //     0 T1 ON, NOTE 67 VOLUME 11
           0x07,0xc0,0x47,0x0a, //   960 T2 ON, NOTE 71 VOLUME 10
                     0x80,0x80, //     0 T1 OFF
           0x07,0xc0,0x32,0x08, //   960 T2 ON, NOTE 50 VOLUME 8
                0x80,0xc5,0x09, //     0 T1 ON, NOTE 69 VOLUME 9
           0x07,0xc0,0x42,0x08, //   960 T2 ON, NOTE 66 VOLUME 8
                     0x93,0x80, //    19 T1 OFF
           0x07,0xad,0x3e,0x08, //   941 T2 ON, NOTE 62 VOLUME 8
                0x80,0xc2,0x08, //     0 T1 ON, NOTE 66 VOLUME 8
                0x93,0x32,0x08, //    19 T2 ON, NOTE 50 VOLUME 8
                0x80,0xbe,0x08, //     0 T1 ON, NOTE 62 VOLUME 8
                0x06,0xfc,0x80, //   892 T1 OFF
                0xb1,0x3e,0x09, //    49 T2 ON, NOTE 62 VOLUME 9
           0x03,0xe0,0x3e,0x0a, //   480 T2 ON, NOTE 62 VOLUME 10
           0x03,0xe0,0x2b,0x08, //   480 T2 ON, NOTE 43 VOLUME 8
                0x80,0xbe,0x09, //     0 T1 ON, NOTE 62 VOLUME 9
           0x07,0xc0,0x3e,0x0a, //   960 T2 ON, NOTE 62 VOLUME 10
                     0x80,0x80, //     0 T1 OFF
           0x03,0xe0,0x3e,0x09, //   480 T2 ON, NOTE 62 VOLUME 9
           0x03,0xe0,0x32,0x09, //   480 T2 ON, NOTE 50 VOLUME 9
                0x80,0xbe,0x0a, //     0 T1 ON, NOTE 62 VOLUME 10
           0x07,0xc0,0x3e,0x09, //   960 T2 ON, NOTE 62 VOLUME 9
                     0x80,0x80, //     0 T1 OFF
           0x03,0xe0,0x3e,0x0a, //   480 T2 ON, NOTE 62 VOLUME 10
           0x03,0xe0,0x2b,0x08, //   480 T2 ON, NOTE 43 VOLUME 8
                0x80,0xc3,0x0a, //     0 T1 ON, NOTE 67 VOLUME 10
           0x07,0xc0,0x45,0x0a, //   960 T2 ON, NOTE 69 VOLUME 10
                     0x80,0x80, //     0 T1 OFF
           0x07,0xc0,0x32,0x08, //   960 T2 ON, NOTE 50 VOLUME 8
                0x80,0xc7,0x0a, //     0 T1 ON, NOTE 71 VOLUME 10
           0x07,0xc0,0x43,0x08, //   960 T2 ON, NOTE 67 VOLUME 8
                     0x80,0x80, //     0 T1 OFF
           0x03,0xe0,0x47,0x0a, //   480 T2 ON, NOTE 71 VOLUME 10
           0x03,0xe0,0x26,0x09, //   480 T2 ON, NOTE 38 VOLUME 9
                0x80,0xca,0x0a, //     0 T1 ON, NOTE 74 VOLUME 10
           0x0f,0x80,0x26,0x0a, //  1920 T2 ON, NOTE 38 VOLUME 10
           0x03,0xe0,0x48,0x0a, //   480 T2 ON, NOTE 72 VOLUME 10
                0xad,0x26,0x0a, //    45 T2 ON, NOTE 38 VOLUME 10
                0x80,0xc8,0x0a, //     0 T1 ON, NOTE 72 VOLUME 10
           0x03,0xb3,0x47,0x09, //   435 T2 ON, NOTE 71 VOLUME 9
                0x88,0x26,0x0a, //     8 T2 ON, NOTE 38 VOLUME 10
                0x80,0xc7,0x09, //     0 T1 ON, NOTE 71 VOLUME 9
           0x03,0xd8,0x45,0x08, //   472 T2 ON, NOTE 69 VOLUME 8
                0x88,0x26,0x0a, //     8 T2 ON, NOTE 38 VOLUME 10
                0x80,0xc5,0x08, //     0 T1 ON, NOTE 69 VOLUME 8
                0x03,0xbe,0x80, //   446 T1 OFF
                0x9a,0x2b,0x0c, //    26 T2 ON, NOTE 43 VOLUME 12
                0x80,0xc3,0x0c, //     0 T1 ON, NOTE 67 VOLUME 12
           0x07,0xc0,0xc7,0x0c, //   960 T1 ON, NOTE 71 VOLUME 12
           0x07,0xc0,0xc3,0x0c, //   960 T1 ON, NOTE 67 VOLUME 12
                0x07,0xc0,0x01, //   960 BOTH OFF
                     0x80,0x04  //     0 END OF FILE
};
