#include "MIDIPlayer.h"

// converted from tchaikovksy_sugar_plum.mid - 2324 bytes total
extern const byte SUGAR_PLUM_FAIRY[] PROGMEM = 
{
      0x02,0x80,0x1e,0x42,0xa0, //      0 BEGIN PROGRAM (256 ticks/beat, tempo = 500000 us/beat)
                0x80,0xb2,0x04, //      0 T1 ON, NOTE  50 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xbe,0x04, //    129 T1 ON, NOTE  62 VOLUME  4
                0x80,0x39,0x04, //      0 T2 ON, NOTE  57 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xb2,0x04, //    129 T1 ON, NOTE  50 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xc0,0x04, //    129 T1 ON, NOTE  64 VOLUME  4
                0x80,0x3a,0x04, //      0 T2 ON, NOTE  58 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xb2,0x04, //    129 T1 ON, NOTE  50 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xc1,0x04, //    129 T1 ON, NOTE  65 VOLUME  4
                0x80,0x3b,0x04, //      0 T2 ON, NOTE  59 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xb2,0x04, //    129 T1 ON, NOTE  50 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xbd,0x04, //    129 T1 ON, NOTE  61 VOLUME  4
                0x80,0x3a,0x04, //      0 T2 ON, NOTE  58 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xb2,0x04, //    129 T1 ON, NOTE  50 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xbe,0x04, //    129 T1 ON, NOTE  62 VOLUME  4
                0x80,0x39,0x04, //      0 T2 ON, NOTE  57 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xb2,0x04, //    129 T1 ON, NOTE  50 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xc0,0x04, //    129 T1 ON, NOTE  64 VOLUME  4
                0x80,0x3a,0x04, //      0 T2 ON, NOTE  58 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xb2,0x05, //    129 T1 ON, NOTE  50 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xc1,0x04, //    129 T1 ON, NOTE  65 VOLUME  4
                0x80,0x3b,0x04, //      0 T2 ON, NOTE  59 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xb2,0x04, //    129 T1 ON, NOTE  50 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xbd,0x04, //    129 T1 ON, NOTE  61 VOLUME  4
                0x80,0x3a,0x04, //      0 T2 ON, NOTE  58 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xb2,0x04, //    129 T1 ON, NOTE  50 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd9,0x04, //    129 T1 ON, NOTE  89 VOLUME  4
                0x80,0x51,0x04, //      0 T2 ON, NOTE  81 VOLUME  4
                0xbf,0xb9,0x05, //     63 T1 ON, NOTE  57 VOLUME  5
                0x80,0x35,0x05, //      0 T2 ON, NOTE  53 VOLUME  5
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd6,0x04, //      1 T1 ON, NOTE  86 VOLUME  4
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd9,0x05, //     65 T1 ON, NOTE  89 VOLUME  5
                0x80,0x51,0x05, //      0 T2 ON, NOTE  81 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd8,0x05, //    129 T1 ON, NOTE  88 VOLUME  5
                0x80,0x4f,0x05, //      0 T2 ON, NOTE  79 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd5,0x04, //    129 T1 ON, NOTE  85 VOLUME  4
                0x80,0x4c,0x04, //      0 T2 ON, NOTE  76 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd6,0x05, //    129 T1 ON, NOTE  86 VOLUME  5
                0x80,0x4d,0x05, //      0 T2 ON, NOTE  77 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd4,0x04, //    129 T1 ON, NOTE  84 VOLUME  4
                0x80,0x4e,0x04, //      0 T2 ON, NOTE  78 VOLUME  4
                0xbf,0xb2,0x04, //     63 T1 ON, NOTE  50 VOLUME  4
                     0x80,0x00, //      0 T2 OFF
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd4,0x05, //      1 T1 ON, NOTE  84 VOLUME  5
                0x80,0x4e,0x05, //      0 T2 ON, NOTE  78 VOLUME  5
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd4,0x04, //     65 T1 ON, NOTE  84 VOLUME  4
                0x80,0x4e,0x04, //      0 T2 ON, NOTE  78 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd3,0x04, //    129 T1 ON, NOTE  83 VOLUME  4
                0x80,0x4d,0x04, //      0 T2 ON, NOTE  77 VOLUME  4
                0xbf,0xb2,0x04, //     63 T1 ON, NOTE  50 VOLUME  4
                     0x80,0x00, //      0 T2 OFF
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd3,0x05, //      1 T1 ON, NOTE  83 VOLUME  5
                0x80,0x4d,0x05, //      0 T2 ON, NOTE  77 VOLUME  5
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd3,0x05, //     65 T1 ON, NOTE  83 VOLUME  5
                0x80,0x4d,0x05, //      0 T2 ON, NOTE  77 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd2,0x04, //    129 T1 ON, NOTE  82 VOLUME  4
                0x80,0x4c,0x04, //      0 T2 ON, NOTE  76 VOLUME  4
                0xbf,0xb2,0x04, //     63 T1 ON, NOTE  50 VOLUME  4
                     0x80,0x00, //      0 T2 OFF
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd2,0x04, //      1 T1 ON, NOTE  82 VOLUME  4
                0x80,0x4c,0x04, //      0 T2 ON, NOTE  76 VOLUME  4
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd2,0x05, //     65 T1 ON, NOTE  82 VOLUME  5
                0x80,0x4c,0x05, //      0 T2 ON, NOTE  76 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd1,0x05, //    129 T1 ON, NOTE  81 VOLUME  5
                0x80,0x4d,0x05, //      0 T2 ON, NOTE  77 VOLUME  5
                0xbf,0xb2,0x04, //     63 T1 ON, NOTE  50 VOLUME  4
                     0x80,0x00, //      0 T2 OFF
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd6,0x05, //      1 T1 ON, NOTE  86 VOLUME  5
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd2,0x04, //     65 T1 ON, NOTE  82 VOLUME  4
                0x80,0x4f,0x04, //      0 T2 ON, NOTE  79 VOLUME  4
                0xbf,0xbe,0x06, //     63 T1 ON, NOTE  62 VOLUME  6
                     0x80,0x00, //      0 T2 OFF
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd6,0x05, //      1 T1 ON, NOTE  86 VOLUME  5
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd1,0x04, //     65 T1 ON, NOTE  81 VOLUME  4
                0x80,0x4d,0x04, //      0 T2 ON, NOTE  77 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xbe,0x04, //    129 T1 ON, NOTE  62 VOLUME  4
                0xc0,0xbc,0x04, //     64 T1 ON, NOTE  60 VOLUME  4
                0xc0,0xbb,0x04, //     64 T1 ON, NOTE  59 VOLUME  4
                0xc0,0xb9,0x04, //     64 T1 ON, NOTE  57 VOLUME  4
                0xc0,0xb8,0x04, //     64 T1 ON, NOTE  56 VOLUME  4
                0x01,0xcd,0x01, //    205 BOTH OFF
                0xb3,0xcd,0x04, //     51 T1 ON, NOTE  77 VOLUME  4
                0x80,0x46,0x04, //      0 T2 ON, NOTE  70 VOLUME  4
                0xbf,0xc1,0x06, //     63 T1 ON, NOTE  65 VOLUME  6
                0x80,0x3e,0x06, //      0 T2 ON, NOTE  62 VOLUME  6
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xca,0x04, //      1 T1 ON, NOTE  74 VOLUME  4
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xcd,0x05, //     65 T1 ON, NOTE  77 VOLUME  5
                0x80,0x46,0x05, //      0 T2 ON, NOTE  70 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xcc,0x04, //    129 T1 ON, NOTE  76 VOLUME  4
                0x80,0x46,0x04, //      0 T2 ON, NOTE  70 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd2,0x05, //    129 T1 ON, NOTE  82 VOLUME  5
                0x80,0x4c,0x05, //      0 T2 ON, NOTE  76 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd1,0x05, //    129 T1 ON, NOTE  81 VOLUME  5
                0x80,0x4d,0x05, //      0 T2 ON, NOTE  77 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd9,0x04, //    129 T1 ON, NOTE  89 VOLUME  4
                0x80,0x50,0x04, //      0 T2 ON, NOTE  80 VOLUME  4
                0xbf,0xb4,0x04, //     63 T1 ON, NOTE  52 VOLUME  4
                     0x80,0x00, //      0 T2 OFF
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd9,0x04, //      1 T1 ON, NOTE  89 VOLUME  4
                0x80,0x50,0x04, //      0 T2 ON, NOTE  80 VOLUME  4
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd9,0x05, //     65 T1 ON, NOTE  89 VOLUME  5
                0x80,0x50,0x05, //      0 T2 ON, NOTE  80 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd8,0x04, //    129 T1 ON, NOTE  88 VOLUME  4
                0x80,0x54,0x04, //      0 T2 ON, NOTE  84 VOLUME  4
                0xbf,0xb4,0x04, //     63 T1 ON, NOTE  52 VOLUME  4
                     0x80,0x00, //      0 T2 OFF
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd8,0x04, //      1 T1 ON, NOTE  88 VOLUME  4
                0x80,0x54,0x04, //      0 T2 ON, NOTE  84 VOLUME  4
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd8,0x05, //     65 T1 ON, NOTE  88 VOLUME  5
                0x80,0x54,0x05, //      0 T2 ON, NOTE  84 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd6,0x05, //    129 T1 ON, NOTE  86 VOLUME  5
                0x80,0x53,0x05, //      0 T2 ON, NOTE  83 VOLUME  5
                0xbf,0xb4,0x05, //     63 T1 ON, NOTE  52 VOLUME  5
                     0x80,0x00, //      0 T2 OFF
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd6,0x05, //      1 T1 ON, NOTE  86 VOLUME  5
                0x80,0x53,0x05, //      0 T2 ON, NOTE  83 VOLUME  5
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd6,0x04, //     65 T1 ON, NOTE  86 VOLUME  4
                0x80,0x53,0x04, //      0 T2 ON, NOTE  83 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd5,0x05, //    129 T1 ON, NOTE  85 VOLUME  5
                0x80,0x51,0x05, //      0 T2 ON, NOTE  81 VOLUME  5
                0xbf,0xc0,0x05, //     63 T1 ON, NOTE  64 VOLUME  5
                0x80,0x39,0x05, //      0 T2 ON, NOTE  57 VOLUME  5
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd8,0x05, //      1 T1 ON, NOTE  88 VOLUME  5
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd6,0x04, //     65 T1 ON, NOTE  86 VOLUME  4
                0x80,0x50,0x04, //      0 T2 ON, NOTE  80 VOLUME  4
                0xbf,0xc0,0x04, //     63 T1 ON, NOTE  64 VOLUME  4
                0x80,0x3a,0x04, //      0 T2 ON, NOTE  58 VOLUME  4
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd8,0x05, //      1 T1 ON, NOTE  88 VOLUME  5
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd5,0x04, //     65 T1 ON, NOTE  85 VOLUME  4
                0x80,0x51,0x04, //      0 T2 ON, NOTE  81 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xb9,0x04, //    129 T1 ON, NOTE  57 VOLUME  4
                0xc0,0xb7,0x05, //     64 T1 ON, NOTE  55 VOLUME  5
                0xc0,0xb5,0x04, //     64 T1 ON, NOTE  53 VOLUME  4
                0xc0,0xb4,0x05, //     64 T1 ON, NOTE  52 VOLUME  5
                0xc0,0xb2,0x04, //     64 T1 ON, NOTE  50 VOLUME  4
                     0xe5,0x01, //    101 BOTH OFF
           0x01,0x9b,0xd9,0x04, //    155 T1 ON, NOTE  89 VOLUME  4
                0x80,0x51,0x04, //      0 T2 ON, NOTE  81 VOLUME  4
                0xbf,0xb9,0x05, //     63 T1 ON, NOTE  57 VOLUME  5
                0x80,0x35,0x05, //      0 T2 ON, NOTE  53 VOLUME  5
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd6,0x04, //      1 T1 ON, NOTE  86 VOLUME  4
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd9,0x05, //     65 T1 ON, NOTE  89 VOLUME  5
                0x80,0x51,0x05, //      0 T2 ON, NOTE  81 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd8,0x04, //    129 T1 ON, NOTE  88 VOLUME  4
                0x80,0x4f,0x04, //      0 T2 ON, NOTE  79 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd5,0x05, //    129 T1 ON, NOTE  85 VOLUME  5
                0x80,0x4c,0x05, //      0 T2 ON, NOTE  76 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd6,0x05, //    129 T1 ON, NOTE  86 VOLUME  5
                0x80,0x4d,0x05, //      0 T2 ON, NOTE  77 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd4,0x04, //    129 T1 ON, NOTE  84 VOLUME  4
                0x80,0x4e,0x04, //      0 T2 ON, NOTE  78 VOLUME  4
                0xbf,0xb2,0x04, //     63 T1 ON, NOTE  50 VOLUME  4
                     0x80,0x00, //      0 T2 OFF
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd4,0x05, //      1 T1 ON, NOTE  84 VOLUME  5
                0x80,0x4e,0x05, //      0 T2 ON, NOTE  78 VOLUME  5
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd4,0x05, //     65 T1 ON, NOTE  84 VOLUME  5
                0x80,0x4e,0x05, //      0 T2 ON, NOTE  78 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd3,0x05, //    129 T1 ON, NOTE  83 VOLUME  5
                0x80,0x4d,0x05, //      0 T2 ON, NOTE  77 VOLUME  5
                0xbf,0xb2,0x04, //     63 T1 ON, NOTE  50 VOLUME  4
                     0x80,0x00, //      0 T2 OFF
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd3,0x04, //      1 T1 ON, NOTE  83 VOLUME  4
                0x80,0x4d,0x04, //      0 T2 ON, NOTE  77 VOLUME  4
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd3,0x05, //     65 T1 ON, NOTE  83 VOLUME  5
                0x80,0x4d,0x05, //      0 T2 ON, NOTE  77 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd2,0x05, //    129 T1 ON, NOTE  82 VOLUME  5
                0x80,0x4c,0x05, //      0 T2 ON, NOTE  76 VOLUME  5
                0xbf,0xb2,0x04, //     63 T1 ON, NOTE  50 VOLUME  4
                     0x80,0x00, //      0 T2 OFF
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd2,0x04, //      1 T1 ON, NOTE  82 VOLUME  4
                0x80,0x4c,0x04, //      0 T2 ON, NOTE  76 VOLUME  4
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd2,0x04, //     65 T1 ON, NOTE  82 VOLUME  4
                0x80,0x4c,0x04, //      0 T2 ON, NOTE  76 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd1,0x04, //    129 T1 ON, NOTE  81 VOLUME  4
                0x80,0x4d,0x04, //      0 T2 ON, NOTE  77 VOLUME  4
                0xbf,0xb2,0x05, //     63 T1 ON, NOTE  50 VOLUME  5
                     0x80,0x00, //      0 T2 OFF
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd6,0x05, //      1 T1 ON, NOTE  86 VOLUME  5
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd2,0x04, //     65 T1 ON, NOTE  82 VOLUME  4
                0x80,0x4f,0x04, //      0 T2 ON, NOTE  79 VOLUME  4
                0xbf,0xc0,0x06, //     63 T1 ON, NOTE  64 VOLUME  6
                0x80,0x3e,0x06, //      0 T2 ON, NOTE  62 VOLUME  6
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd6,0x05, //      1 T1 ON, NOTE  86 VOLUME  5
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd1,0x04, //     65 T1 ON, NOTE  81 VOLUME  4
                0x80,0x4d,0x04, //      0 T2 ON, NOTE  77 VOLUME  4
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xc1,0x05, //    129 T1 ON, NOTE  65 VOLUME  5
                0xc0,0xc0,0x05, //     64 T1 ON, NOTE  64 VOLUME  5
                0xc0,0xbe,0x04, //     64 T1 ON, NOTE  62 VOLUME  4
                0xc0,0xbc,0x04, //     64 T1 ON, NOTE  60 VOLUME  4
                0xc0,0xbb,0x04, //     64 T1 ON, NOTE  59 VOLUME  4
                0x01,0xcd,0x01, //    205 BOTH OFF
                0xb3,0xca,0x04, //     51 T1 ON, NOTE  74 VOLUME  4
                0x80,0x44,0x04, //      0 T2 ON, NOTE  68 VOLUME  4
                0xbf,0xc0,0x08, //     63 T1 ON, NOTE  64 VOLUME  8
                     0x80,0x00, //      0 T2 OFF
                0xc1,0x47,0x04, //     65 T2 ON, NOTE  71 VOLUME  4
                     0xbf,0x00, //     63 T2 OFF
                0xc1,0xca,0x05, //     65 T1 ON, NOTE  74 VOLUME  5
                0x80,0x44,0x05, //      0 T2 ON, NOTE  68 VOLUME  5
                0xff,0xc0,0x08, //    127 T1 ON, NOTE  64 VOLUME  8
                     0x80,0x00, //      0 T2 OFF
           0x01,0x81,0xc9,0x04, //    129 T1 ON, NOTE  73 VOLUME  4
                0x80,0x45,0x04, //      0 T2 ON, NOTE  69 VOLUME  4
                0xff,0xb9,0x04, //    127 T1 ON, NOTE  57 VOLUME  4
                     0x80,0x00, //      0 T2 OFF
                     0xce,0x01, //     78 BOTH OFF
                0xb3,0xb2,0x05, //     51 T1 ON, NOTE  50 VOLUME  5
           0x02,0x80,0xc8,0x04, //    256 T1 ON, NOTE  72 VOLUME  4
                0x80,0x42,0x04, //      0 T2 ON, NOTE  66 VOLUME  4
                0xbf,0xbe,0x08, //     63 T1 ON, NOTE  62 VOLUME  8
                     0x80,0x00, //      0 T2 OFF
                0xc1,0x45,0x04, //     65 T2 ON, NOTE  69 VOLUME  4
                     0xbf,0x00, //     63 T2 OFF
                0xc1,0xc8,0x05, //     65 T1 ON, NOTE  72 VOLUME  5
                0x80,0x42,0x05, //      0 T2 ON, NOTE  66 VOLUME  5
                0xff,0xbe,0x08, //    127 T1 ON, NOTE  62 VOLUME  8
                     0x80,0x00, //      0 T2 OFF
           0x01,0x81,0xc7,0x04, //    129 T1 ON, NOTE  71 VOLUME  4
                0x80,0x43,0x04, //      0 T2 ON, NOTE  67 VOLUME  4
                0xff,0xb7,0x04, //    127 T1 ON, NOTE  55 VOLUME  4
                     0x80,0x00, //      0 T2 OFF
                     0xce,0x01, //     78 BOTH OFF
                0xb3,0xb0,0x04, //     51 T1 ON, NOTE  48 VOLUME  4
           0x02,0x80,0xc6,0x04, //    256 T1 ON, NOTE  70 VOLUME  4
                0x80,0x40,0x04, //      0 T2 ON, NOTE  64 VOLUME  4
                0xbf,0xbc,0x09, //     63 T1 ON, NOTE  60 VOLUME  9
                     0x80,0x00, //      0 T2 OFF
                0xc1,0x43,0x04, //     65 T2 ON, NOTE  67 VOLUME  4
                     0xbf,0x00, //     63 T2 OFF
                0xc1,0xc6,0x05, //     65 T1 ON, NOTE  70 VOLUME  5
                0x80,0x40,0x05, //      0 T2 ON, NOTE  64 VOLUME  5
                0xff,0xbc,0x09, //    127 T1 ON, NOTE  60 VOLUME  9
                     0x80,0x00, //      0 T2 OFF
           0x01,0x81,0xc5,0x04, //    129 T1 ON, NOTE  69 VOLUME  4
                0x80,0x41,0x04, //      0 T2 ON, NOTE  65 VOLUME  4
                0xff,0xb5,0x04, //    127 T1 ON, NOTE  53 VOLUME  4
                     0x80,0x00, //      0 T2 OFF
                     0xce,0x01, //     78 BOTH OFF
                0xb3,0xb9,0x05, //     51 T1 ON, NOTE  57 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xc5,0x04, //    129 T1 ON, NOTE  69 VOLUME  4
                0x80,0x37,0x04, //      0 T2 ON, NOTE  55 VOLUME  4
                0xa8,0x49,0x04, //     40 T2 ON, NOTE  73 VOLUME  4
                0xa8,0xd1,0x04, //     40 T1 ON, NOTE  81 VOLUME  4
           0x01,0x81,0xca,0x04, //    129 T1 ON, NOTE  74 VOLUME  4
                0x80,0x35,0x05, //      0 T2 ON, NOTE  53 VOLUME  5
                     0xff,0x00, //    127 T2 OFF
           0x01,0x81,0xad,0x08, //    129 T1 ON, NOTE  45 VOLUME  8
           0x02,0x80,0xb5,0x06, //    256 T1 ON, NOTE  53 VOLUME  6
                0x80,0x32,0x06, //      0 T2 ON, NOTE  50 VOLUME  6
           0x01,0x80,0x3b,0x04, //    128 T2 ON, NOTE  59 VOLUME  4
                0xbf,0x32,0x06, //     63 T2 ON, NOTE  50 VOLUME  6
                0xc1,0xb7,0x05, //     65 T1 ON, NOTE  55 VOLUME  5
                0x80,0x34,0x05, //      0 T2 ON, NOTE  52 VOLUME  5
           0x01,0x80,0x3d,0x05, //    128 T2 ON, NOTE  61 VOLUME  5
                0xbf,0x34,0x05, //     63 T2 ON, NOTE  52 VOLUME  5
                0xc1,0xb5,0x05, //     65 T1 ON, NOTE  53 VOLUME  5
                0x80,0x2d,0x08, //      0 T2 ON, NOTE  45 VOLUME  8
           0x01,0x80,0xbe,0x06, //    128 T1 ON, NOTE  62 VOLUME  6
                0x80,0x39,0x06, //      0 T2 ON, NOTE  57 VOLUME  6
                0xbf,0xb5,0x05, //     63 T1 ON, NOTE  53 VOLUME  5
                0x80,0x2d,0x08, //      0 T2 ON, NOTE  45 VOLUME  8
                0xc1,0xb7,0x06, //     65 T1 ON, NOTE  55 VOLUME  6
           0x01,0x80,0xc0,0x07, //    128 T1 ON, NOTE  64 VOLUME  7
                0x80,0x39,0x07, //      0 T2 ON, NOTE  57 VOLUME  7
                0xbf,0xb7,0x06, //     63 T1 ON, NOTE  55 VOLUME  6
                0x80,0x2d,0x08, //      0 T2 ON, NOTE  45 VOLUME  8
                0xc1,0xb9,0x07, //     65 T1 ON, NOTE  57 VOLUME  7
           0x01,0x80,0xc1,0x07, //    128 T1 ON, NOTE  65 VOLUME  7
                0x80,0x3e,0x07, //      0 T2 ON, NOTE  62 VOLUME  7
                0xbf,0xb9,0x07, //     63 T1 ON, NOTE  57 VOLUME  7
                0x80,0x2d,0x08, //      0 T2 ON, NOTE  45 VOLUME  8
                0xc1,0xb5,0x07, //     65 T1 ON, NOTE  53 VOLUME  7
           0x01,0x80,0xbe,0x06, //    128 T1 ON, NOTE  62 VOLUME  6
                0x80,0x3b,0x06, //      0 T2 ON, NOTE  59 VOLUME  6
           0x01,0x80,0xbd,0x06, //    128 T1 ON, NOTE  61 VOLUME  6
                0x80,0x39,0x06, //      0 T2 ON, NOTE  57 VOLUME  6
           0x01,0xcd,0xb4,0x06, //    205 T1 ON, NOTE  52 VOLUME  6
                0x80,0x2d,0x08, //      0 T2 ON, NOTE  45 VOLUME  8
                0xb3,0xb9,0x07, //     51 T1 ON, NOTE  57 VOLUME  7
                0x80,0x31,0x07, //      0 T2 ON, NOTE  49 VOLUME  7
                0xd5,0xba,0x08, //     85 T1 ON, NOTE  58 VOLUME  8
                0xd5,0xb9,0x07, //     85 T1 ON, NOTE  57 VOLUME  7
                0xc4,0xad,0x07, //     68 T1 ON, NOTE  45 VOLUME  7
                0x92,0xb7,0x08, //     18 T1 ON, NOTE  55 VOLUME  8
                0x80,0x32,0x08, //      0 T2 ON, NOTE  50 VOLUME  8
           0x01,0x80,0xb5,0x08, //    128 T1 ON, NOTE  53 VOLUME  8
                     0xb2,0x80, //     50 T1 OFF
                0xce,0xb5,0x08, //     78 T1 ON, NOTE  53 VOLUME  8
                     0xbf,0x80, //     63 T1 OFF
                0xc1,0xb5,0x08, //     65 T1 ON, NOTE  53 VOLUME  8
                     0xbf,0x80, //     63 T1 OFF
                0xc1,0xb5,0x07, //     65 T1 ON, NOTE  53 VOLUME  7
                     0xbf,0x80, //     63 T1 OFF
                0xc1,0xb5,0x08, //     65 T1 ON, NOTE  53 VOLUME  8
                     0xbf,0x80, //     63 T1 OFF
                     0x8e,0x01, //     14 BOTH OFF
                0xb3,0xb5,0x07, //     51 T1 ON, NOTE  53 VOLUME  7
                0x80,0x2f,0x08, //      0 T2 ON, NOTE  47 VOLUME  8
                0xd5,0xb9,0x08, //     85 T1 ON, NOTE  57 VOLUME  8
                0xd5,0xb7,0x07, //     85 T1 ON, NOTE  55 VOLUME  7
                0xc4,0xab,0x08, //     68 T1 ON, NOTE  43 VOLUME  8
                0x92,0xb5,0x07, //     18 T1 ON, NOTE  53 VOLUME  7
                0x80,0x30,0x09, //      0 T2 ON, NOTE  48 VOLUME  9
           0x01,0x80,0xb4,0x07, //    128 T1 ON, NOTE  52 VOLUME  7
                     0xb2,0x80, //     50 T1 OFF
                0xce,0xb4,0x08, //     78 T1 ON, NOTE  52 VOLUME  8
                     0xbf,0x80, //     63 T1 OFF
                0xc1,0xb4,0x08, //     65 T1 ON, NOTE  52 VOLUME  8
                     0xbf,0x80, //     63 T1 OFF
                0xc1,0xb4,0x08, //     65 T1 ON, NOTE  52 VOLUME  8
                     0xbf,0x80, //     63 T1 OFF
                0xc1,0xb4,0x08, //     65 T1 ON, NOTE  52 VOLUME  8
                     0xbf,0x80, //     63 T1 OFF
                     0x8e,0x01, //     14 BOTH OFF
                0xb3,0xad,0x09, //     51 T1 ON, NOTE  45 VOLUME  9
           0x02,0x80,0xb5,0x05, //    256 T1 ON, NOTE  53 VOLUME  5
                0x80,0x32,0x05, //      0 T2 ON, NOTE  50 VOLUME  5
           0x01,0x80,0x3b,0x04, //    128 T2 ON, NOTE  59 VOLUME  4
                0xbf,0x32,0x05, //     63 T2 ON, NOTE  50 VOLUME  5
                0xc1,0xb7,0x05, //     65 T1 ON, NOTE  55 VOLUME  5
                0x80,0x34,0x05, //      0 T2 ON, NOTE  52 VOLUME  5
           0x01,0x80,0x3d,0x05, //    128 T2 ON, NOTE  61 VOLUME  5
                0xbf,0x34,0x05, //     63 T2 ON, NOTE  52 VOLUME  5
                0xc1,0xb5,0x05, //     65 T1 ON, NOTE  53 VOLUME  5
                0x80,0x2d,0x09, //      0 T2 ON, NOTE  45 VOLUME  9
           0x01,0x80,0xbe,0x06, //    128 T1 ON, NOTE  62 VOLUME  6
                0x80,0x39,0x06, //      0 T2 ON, NOTE  57 VOLUME  6
                0xbf,0xb5,0x05, //     63 T1 ON, NOTE  53 VOLUME  5
                0x80,0x2d,0x09, //      0 T2 ON, NOTE  45 VOLUME  9
                0xc1,0xb7,0x06, //     65 T1 ON, NOTE  55 VOLUME  6
           0x01,0x80,0xc0,0x07, //    128 T1 ON, NOTE  64 VOLUME  7
                0x80,0x39,0x07, //      0 T2 ON, NOTE  57 VOLUME  7
                0xbf,0xb7,0x06, //     63 T1 ON, NOTE  55 VOLUME  6
                0x80,0x2d,0x09, //      0 T2 ON, NOTE  45 VOLUME  9
                0xc1,0xb9,0x08, //     65 T1 ON, NOTE  57 VOLUME  8
           0x01,0x80,0xc1,0x07, //    128 T1 ON, NOTE  65 VOLUME  7
                0x80,0x3e,0x07, //      0 T2 ON, NOTE  62 VOLUME  7
                0xbf,0xb9,0x08, //     63 T1 ON, NOTE  57 VOLUME  8
                0x80,0x2d,0x09, //      0 T2 ON, NOTE  45 VOLUME  9
                0xc1,0xb5,0x07, //     65 T1 ON, NOTE  53 VOLUME  7
           0x01,0x80,0xbe,0x06, //    128 T1 ON, NOTE  62 VOLUME  6
                0x80,0x3b,0x06, //      0 T2 ON, NOTE  59 VOLUME  6
           0x01,0x80,0xbd,0x06, //    128 T1 ON, NOTE  61 VOLUME  6
                0x80,0x39,0x06, //      0 T2 ON, NOTE  57 VOLUME  6
           0x01,0xcd,0xb4,0x06, //    205 T1 ON, NOTE  52 VOLUME  6
                0x80,0x2d,0x09, //      0 T2 ON, NOTE  45 VOLUME  9
                0xb3,0xb9,0x07, //     51 T1 ON, NOTE  57 VOLUME  7
                0x80,0x31,0x08, //      0 T2 ON, NOTE  49 VOLUME  8
                0xd5,0xba,0x08, //     85 T1 ON, NOTE  58 VOLUME  8
                0xd5,0xb9,0x07, //     85 T1 ON, NOTE  57 VOLUME  7
                0xc4,0xad,0x08, //     68 T1 ON, NOTE  45 VOLUME  8
                0x92,0xb7,0x08, //     18 T1 ON, NOTE  55 VOLUME  8
                0x80,0x32,0x08, //      0 T2 ON, NOTE  50 VOLUME  8
           0x01,0x80,0xb5,0x07, //    128 T1 ON, NOTE  53 VOLUME  7
                     0xb2,0x80, //     50 T1 OFF
                0xce,0xb5,0x08, //     78 T1 ON, NOTE  53 VOLUME  8
                     0xbf,0x80, //     63 T1 OFF
                0xc1,0xb5,0x08, //     65 T1 ON, NOTE  53 VOLUME  8
                     0xbf,0x80, //     63 T1 OFF
                0xc1,0xb5,0x08, //     65 T1 ON, NOTE  53 VOLUME  8
                     0xbf,0x80, //     63 T1 OFF
                0xc1,0xb5,0x08, //     65 T1 ON, NOTE  53 VOLUME  8
                     0xbf,0x80, //     63 T1 OFF
                     0x8e,0x01, //     14 BOTH OFF
                0xb3,0xb5,0x08, //     51 T1 ON, NOTE  53 VOLUME  8
                0x80,0x2f,0x07, //      0 T2 ON, NOTE  47 VOLUME  7
                0xd5,0xb9,0x08, //     85 T1 ON, NOTE  57 VOLUME  8
                0xd5,0xb7,0x08, //     85 T1 ON, NOTE  55 VOLUME  8
                0xc4,0xab,0x07, //     68 T1 ON, NOTE  43 VOLUME  7
                0x92,0xb5,0x08, //     18 T1 ON, NOTE  53 VOLUME  8
                0x80,0x30,0x08, //      0 T2 ON, NOTE  48 VOLUME  8
           0x01,0x80,0xb4,0x08, //    128 T1 ON, NOTE  52 VOLUME  8
                     0xb2,0x80, //     50 T1 OFF
                0xce,0xb4,0x08, //     78 T1 ON, NOTE  52 VOLUME  8
                     0xbf,0x80, //     63 T1 OFF
                0xc1,0xb4,0x08, //     65 T1 ON, NOTE  52 VOLUME  8
                     0xbf,0x80, //     63 T1 OFF
                0xc1,0xb4,0x08, //     65 T1 ON, NOTE  52 VOLUME  8
                     0xbf,0x80, //     63 T1 OFF
                0xc1,0xb4,0x08, //     65 T1 ON, NOTE  52 VOLUME  8
                     0xbf,0x80, //     63 T1 OFF
                     0x8e,0x01, //     14 BOTH OFF
                0xb3,0xad,0x07, //     51 T1 ON, NOTE  45 VOLUME  7
           0x02,0x80,0x32,0x07, //    256 T2 ON, NOTE  50 VOLUME  7
           0x01,0x80,0xc7,0x07, //    128 T1 ON, NOTE  71 VOLUME  7
                0x80,0x41,0x07, //      0 T2 ON, NOTE  65 VOLUME  7
           0x01,0x80,0xb4,0x08, //    128 T1 ON, NOTE  52 VOLUME  8
                0x80,0x2d,0x07, //      0 T2 ON, NOTE  45 VOLUME  7
           0x01,0x80,0xc9,0x07, //    128 T1 ON, NOTE  73 VOLUME  7
                0x80,0x43,0x07, //      0 T2 ON, NOTE  67 VOLUME  7
           0x01,0x80,0xb5,0x08, //    128 T1 ON, NOTE  53 VOLUME  8
                0x80,0x2d,0x07, //      0 T2 ON, NOTE  45 VOLUME  7
           0x01,0x80,0xca,0x07, //    128 T1 ON, NOTE  74 VOLUME  7
                0x80,0x45,0x07, //      0 T2 ON, NOTE  69 VOLUME  7
                0xb3,0xc5,0x09, //     51 T1 ON, NOTE  69 VOLUME  9
                0x80,0x35,0x08, //      0 T2 ON, NOTE  53 VOLUME  8
           0x01,0xcd,0x2d,0x07, //    205 T2 ON, NOTE  45 VOLUME  7
                0xb3,0xb4,0x08, //     51 T1 ON, NOTE  52 VOLUME  8
           0x01,0x80,0xc9,0x08, //    128 T1 ON, NOTE  73 VOLUME  8
                0x80,0x43,0x08, //      0 T2 ON, NOTE  67 VOLUME  8
           0x01,0x80,0xb5,0x08, //    128 T1 ON, NOTE  53 VOLUME  8
                0x80,0x2d,0x07, //      0 T2 ON, NOTE  45 VOLUME  7
           0x01,0x80,0xca,0x08, //    128 T1 ON, NOTE  74 VOLUME  8
                0x80,0x45,0x08, //      0 T2 ON, NOTE  69 VOLUME  8
           0x01,0x80,0xb7,0x08, //    128 T1 ON, NOTE  55 VOLUME  8
                0x80,0x2d,0x07, //      0 T2 ON, NOTE  45 VOLUME  7
           0x01,0x80,0xcc,0x09, //    128 T1 ON, NOTE  76 VOLUME  9
                0x80,0x49,0x09, //      0 T2 ON, NOTE  73 VOLUME  9
                0xb3,0xc5,0x09, //     51 T1 ON, NOTE  69 VOLUME  9
                0x80,0x37,0x08, //      0 T2 ON, NOTE  55 VOLUME  8
           0x01,0xcd,0x2d,0x08, //    205 T2 ON, NOTE  45 VOLUME  8
                0xb3,0xb5,0x09, //     51 T1 ON, NOTE  53 VOLUME  9
           0x01,0x80,0xca,0x09, //    128 T1 ON, NOTE  74 VOLUME  9
                0x80,0x47,0x09, //      0 T2 ON, NOTE  71 VOLUME  9
           0x01,0x80,0xb7,0x0a, //    128 T1 ON, NOTE  55 VOLUME 10
                0x80,0x2d,0x08, //      0 T2 ON, NOTE  45 VOLUME  8
           0x01,0x80,0xcc,0x0a, //    128 T1 ON, NOTE  76 VOLUME 10
                0x80,0x49,0x0a, //      0 T2 ON, NOTE  73 VOLUME 10
           0x01,0x80,0xb9,0x0a, //    128 T1 ON, NOTE  57 VOLUME 10
                0x80,0x2d,0x08, //      0 T2 ON, NOTE  45 VOLUME  8
           0x01,0x80,0xcd,0x0a, //    128 T1 ON, NOTE  77 VOLUME 10
                0x80,0x4a,0x0a, //      0 T2 ON, NOTE  74 VOLUME 10
                0xb3,0xb9,0x09, //     51 T1 ON, NOTE  57 VOLUME  9
                0x80,0x39,0x0a, //      0 T2 ON, NOTE  57 VOLUME 10
           0x01,0x80,0xcd,0x0a, //    128 T1 ON, NOTE  77 VOLUME 10
                0x80,0x4a,0x0a, //      0 T2 ON, NOTE  74 VOLUME 10
           0x01,0x80,0xc3,0x0c, //    128 T1 ON, NOTE  67 VOLUME 12
                0x80,0x3e,0x0c, //      0 T2 ON, NOTE  62 VOLUME 12
           0x01,0x80,0xcf,0x08, //    128 T1 ON, NOTE  79 VOLUME  8
                0x80,0x4a,0x08, //      0 T2 ON, NOTE  74 VOLUME  8
           0x01,0x80,0xc3,0x09, //    128 T1 ON, NOTE  67 VOLUME  9
                0x80,0x3e,0x09, //      0 T2 ON, NOTE  62 VOLUME  9
           0x01,0x80,0xcf,0x08, //    128 T1 ON, NOTE  79 VOLUME  8
                0x80,0x4a,0x08, //      0 T2 ON, NOTE  74 VOLUME  8
           0x01,0x80,0xd1,0x0a, //    128 T1 ON, NOTE  81 VOLUME 10
                0x80,0x49,0x0a, //      0 T2 ON, NOTE  73 VOLUME 10
           0x02,0x80,0xb9,0x08, //    256 T1 ON, NOTE  57 VOLUME  8
                     0x80,0x00, //      0 T2 OFF
                0xc0,0xb7,0x09, //     64 T1 ON, NOTE  55 VOLUME  9
                0xc0,0xb5,0x09, //     64 T1 ON, NOTE  53 VOLUME  9
                0xc0,0xb4,0x09, //     64 T1 ON, NOTE  52 VOLUME  9
                0xc0,0xb2,0x05, //     64 T1 ON, NOTE  50 VOLUME  5
                     0xe5,0x01, //    101 BOTH OFF
           0x01,0x9b,0xd9,0x05, //    155 T1 ON, NOTE  89 VOLUME  5
                0x80,0x51,0x05, //      0 T2 ON, NOTE  81 VOLUME  5
                0xbf,0xb9,0x07, //     63 T1 ON, NOTE  57 VOLUME  7
                0x80,0x35,0x07, //      0 T2 ON, NOTE  53 VOLUME  7
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd6,0x05, //      1 T1 ON, NOTE  86 VOLUME  5
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd9,0x06, //     65 T1 ON, NOTE  89 VOLUME  6
                0x80,0x51,0x06, //      0 T2 ON, NOTE  81 VOLUME  6
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd8,0x05, //    129 T1 ON, NOTE  88 VOLUME  5
                0x80,0x4f,0x05, //      0 T2 ON, NOTE  79 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd5,0x05, //    129 T1 ON, NOTE  85 VOLUME  5
                0x80,0x4c,0x05, //      0 T2 ON, NOTE  76 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd6,0x06, //    129 T1 ON, NOTE  86 VOLUME  6
                0x80,0x4d,0x06, //      0 T2 ON, NOTE  77 VOLUME  6
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd4,0x05, //    129 T1 ON, NOTE  84 VOLUME  5
                0x80,0x4e,0x05, //      0 T2 ON, NOTE  78 VOLUME  5
                0xbf,0xb2,0x05, //     63 T1 ON, NOTE  50 VOLUME  5
                     0x80,0x00, //      0 T2 OFF
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd4,0x05, //      1 T1 ON, NOTE  84 VOLUME  5
                0x80,0x4e,0x05, //      0 T2 ON, NOTE  78 VOLUME  5
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd4,0x06, //     65 T1 ON, NOTE  84 VOLUME  6
                0x80,0x4e,0x06, //      0 T2 ON, NOTE  78 VOLUME  6
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd3,0x06, //    129 T1 ON, NOTE  83 VOLUME  6
                0x80,0x4d,0x06, //      0 T2 ON, NOTE  77 VOLUME  6
                0xbf,0xb2,0x05, //     63 T1 ON, NOTE  50 VOLUME  5
                     0x80,0x00, //      0 T2 OFF
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd3,0x06, //      1 T1 ON, NOTE  83 VOLUME  6
                0x80,0x4d,0x06, //      0 T2 ON, NOTE  77 VOLUME  6
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd3,0x05, //     65 T1 ON, NOTE  83 VOLUME  5
                0x80,0x4d,0x05, //      0 T2 ON, NOTE  77 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd2,0x05, //    129 T1 ON, NOTE  82 VOLUME  5
                0x80,0x4c,0x05, //      0 T2 ON, NOTE  76 VOLUME  5
                0xbf,0xb2,0x05, //     63 T1 ON, NOTE  50 VOLUME  5
                     0x80,0x00, //      0 T2 OFF
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd2,0x06, //      1 T1 ON, NOTE  82 VOLUME  6
                0x80,0x4c,0x06, //      0 T2 ON, NOTE  76 VOLUME  6
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd2,0x06, //     65 T1 ON, NOTE  82 VOLUME  6
                0x80,0x4c,0x06, //      0 T2 ON, NOTE  76 VOLUME  6
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd1,0x05, //    129 T1 ON, NOTE  81 VOLUME  5
                0x80,0x4d,0x05, //      0 T2 ON, NOTE  77 VOLUME  5
                0xbf,0xb2,0x05, //     63 T1 ON, NOTE  50 VOLUME  5
                     0x80,0x00, //      0 T2 OFF
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd6,0x06, //      1 T1 ON, NOTE  86 VOLUME  6
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd2,0x05, //     65 T1 ON, NOTE  82 VOLUME  5
                0x80,0x4f,0x05, //      0 T2 ON, NOTE  79 VOLUME  5
                0xbf,0xbe,0x07, //     63 T1 ON, NOTE  62 VOLUME  7
                     0x80,0x00, //      0 T2 OFF
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd6,0x06, //      1 T1 ON, NOTE  86 VOLUME  6
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd1,0x05, //     65 T1 ON, NOTE  81 VOLUME  5
                0x80,0x4d,0x05, //      0 T2 ON, NOTE  77 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xbe,0x05, //    129 T1 ON, NOTE  62 VOLUME  5
                0xc0,0xbc,0x05, //     64 T1 ON, NOTE  60 VOLUME  5
                0xc0,0xbb,0x05, //     64 T1 ON, NOTE  59 VOLUME  5
                0xc0,0xb9,0x06, //     64 T1 ON, NOTE  57 VOLUME  6
                0xc0,0xb8,0x06, //     64 T1 ON, NOTE  56 VOLUME  6
                0x01,0xcd,0x01, //    205 BOTH OFF
                0xb3,0xcd,0x05, //     51 T1 ON, NOTE  77 VOLUME  5
                0x80,0x46,0x05, //      0 T2 ON, NOTE  70 VOLUME  5
                0xbf,0xc1,0x07, //     63 T1 ON, NOTE  65 VOLUME  7
                0x80,0x3e,0x07, //      0 T2 ON, NOTE  62 VOLUME  7
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xca,0x05, //      1 T1 ON, NOTE  74 VOLUME  5
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xcd,0x06, //     65 T1 ON, NOTE  77 VOLUME  6
                0x80,0x46,0x06, //      0 T2 ON, NOTE  70 VOLUME  6
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xcc,0x05, //    129 T1 ON, NOTE  76 VOLUME  5
                0x80,0x46,0x05, //      0 T2 ON, NOTE  70 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd2,0x07, //    129 T1 ON, NOTE  82 VOLUME  7
                0x80,0x4c,0x07, //      0 T2 ON, NOTE  76 VOLUME  7
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd1,0x05, //    129 T1 ON, NOTE  81 VOLUME  5
                0x80,0x4d,0x05, //      0 T2 ON, NOTE  77 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd9,0x05, //    129 T1 ON, NOTE  89 VOLUME  5
                0x80,0x50,0x05, //      0 T2 ON, NOTE  80 VOLUME  5
                0xbf,0xb4,0x05, //     63 T1 ON, NOTE  52 VOLUME  5
                     0x80,0x00, //      0 T2 OFF
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd9,0x05, //      1 T1 ON, NOTE  89 VOLUME  5
                0x80,0x50,0x05, //      0 T2 ON, NOTE  80 VOLUME  5
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd9,0x05, //     65 T1 ON, NOTE  89 VOLUME  5
                0x80,0x50,0x05, //      0 T2 ON, NOTE  80 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd8,0x05, //    129 T1 ON, NOTE  88 VOLUME  5
                0x80,0x54,0x05, //      0 T2 ON, NOTE  84 VOLUME  5
                0xbf,0xb4,0x05, //     63 T1 ON, NOTE  52 VOLUME  5
                     0x80,0x00, //      0 T2 OFF
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd8,0x06, //      1 T1 ON, NOTE  88 VOLUME  6
                0x80,0x54,0x06, //      0 T2 ON, NOTE  84 VOLUME  6
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd8,0x05, //     65 T1 ON, NOTE  88 VOLUME  5
                0x80,0x54,0x05, //      0 T2 ON, NOTE  84 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd6,0x05, //    129 T1 ON, NOTE  86 VOLUME  5
                0x80,0x53,0x05, //      0 T2 ON, NOTE  83 VOLUME  5
                0xbf,0xb4,0x05, //     63 T1 ON, NOTE  52 VOLUME  5
                     0x80,0x00, //      0 T2 OFF
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd6,0x06, //      1 T1 ON, NOTE  86 VOLUME  6
                0x80,0x53,0x06, //      0 T2 ON, NOTE  83 VOLUME  6
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd6,0x06, //     65 T1 ON, NOTE  86 VOLUME  6
                0x80,0x53,0x06, //      0 T2 ON, NOTE  83 VOLUME  6
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd5,0x05, //    129 T1 ON, NOTE  85 VOLUME  5
                0x80,0x51,0x05, //      0 T2 ON, NOTE  81 VOLUME  5
                0xbf,0xc0,0x06, //     63 T1 ON, NOTE  64 VOLUME  6
                0x80,0x39,0x06, //      0 T2 ON, NOTE  57 VOLUME  6
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd8,0x07, //      1 T1 ON, NOTE  88 VOLUME  7
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd6,0x05, //     65 T1 ON, NOTE  86 VOLUME  5
                0x80,0x50,0x05, //      0 T2 ON, NOTE  80 VOLUME  5
                0xbf,0xc0,0x06, //     63 T1 ON, NOTE  64 VOLUME  6
                0x80,0x3a,0x06, //      0 T2 ON, NOTE  58 VOLUME  6
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd8,0x06, //      1 T1 ON, NOTE  88 VOLUME  6
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd5,0x05, //     65 T1 ON, NOTE  85 VOLUME  5
                0x80,0x51,0x05, //      0 T2 ON, NOTE  81 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xb9,0x05, //    129 T1 ON, NOTE  57 VOLUME  5
                0xc0,0xb7,0x05, //     64 T1 ON, NOTE  55 VOLUME  5
                0xc0,0xb5,0x05, //     64 T1 ON, NOTE  53 VOLUME  5
                0xc0,0xb4,0x05, //     64 T1 ON, NOTE  52 VOLUME  5
                0xc0,0xb2,0x05, //     64 T1 ON, NOTE  50 VOLUME  5
                     0xe5,0x01, //    101 BOTH OFF
           0x01,0x9b,0xd9,0x05, //    155 T1 ON, NOTE  89 VOLUME  5
                0x80,0x51,0x05, //      0 T2 ON, NOTE  81 VOLUME  5
                0xbf,0xb9,0x06, //     63 T1 ON, NOTE  57 VOLUME  6
                0x80,0x35,0x06, //      0 T2 ON, NOTE  53 VOLUME  6
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd6,0x05, //      1 T1 ON, NOTE  86 VOLUME  5
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd9,0x06, //     65 T1 ON, NOTE  89 VOLUME  6
                0x80,0x51,0x06, //      0 T2 ON, NOTE  81 VOLUME  6
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd8,0x06, //    129 T1 ON, NOTE  88 VOLUME  6
                0x80,0x4f,0x06, //      0 T2 ON, NOTE  79 VOLUME  6
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd5,0x05, //    129 T1 ON, NOTE  85 VOLUME  5
                0x80,0x4c,0x05, //      0 T2 ON, NOTE  76 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd6,0x06, //    129 T1 ON, NOTE  86 VOLUME  6
                0x80,0x4d,0x06, //      0 T2 ON, NOTE  77 VOLUME  6
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd4,0x05, //    129 T1 ON, NOTE  84 VOLUME  5
                0x80,0x4e,0x05, //      0 T2 ON, NOTE  78 VOLUME  5
                0xbf,0xb2,0x05, //     63 T1 ON, NOTE  50 VOLUME  5
                     0x80,0x00, //      0 T2 OFF
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd4,0x06, //      1 T1 ON, NOTE  84 VOLUME  6
                0x80,0x4e,0x06, //      0 T2 ON, NOTE  78 VOLUME  6
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd4,0x06, //     65 T1 ON, NOTE  84 VOLUME  6
                0x80,0x4e,0x06, //      0 T2 ON, NOTE  78 VOLUME  6
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd3,0x05, //    129 T1 ON, NOTE  83 VOLUME  5
                0x80,0x4d,0x05, //      0 T2 ON, NOTE  77 VOLUME  5
                0xbf,0xb2,0x05, //     63 T1 ON, NOTE  50 VOLUME  5
                     0x80,0x00, //      0 T2 OFF
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd3,0x05, //      1 T1 ON, NOTE  83 VOLUME  5
                0x80,0x4d,0x05, //      0 T2 ON, NOTE  77 VOLUME  5
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd3,0x05, //     65 T1 ON, NOTE  83 VOLUME  5
                0x80,0x4d,0x05, //      0 T2 ON, NOTE  77 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd2,0x06, //    129 T1 ON, NOTE  82 VOLUME  6
                0x80,0x4c,0x06, //      0 T2 ON, NOTE  76 VOLUME  6
                0xbf,0xb2,0x05, //     63 T1 ON, NOTE  50 VOLUME  5
                     0x80,0x00, //      0 T2 OFF
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd2,0x05, //      1 T1 ON, NOTE  82 VOLUME  5
                0x80,0x4c,0x05, //      0 T2 ON, NOTE  76 VOLUME  5
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd2,0x06, //     65 T1 ON, NOTE  82 VOLUME  6
                0x80,0x4c,0x06, //      0 T2 ON, NOTE  76 VOLUME  6
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xd1,0x05, //    129 T1 ON, NOTE  81 VOLUME  5
                0x80,0x4d,0x05, //      0 T2 ON, NOTE  77 VOLUME  5
                0xbf,0xb2,0x05, //     63 T1 ON, NOTE  50 VOLUME  5
                     0x80,0x00, //      0 T2 OFF
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd6,0x06, //      1 T1 ON, NOTE  86 VOLUME  6
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd2,0x05, //     65 T1 ON, NOTE  82 VOLUME  5
                0x80,0x4f,0x05, //      0 T2 ON, NOTE  79 VOLUME  5
                0xbf,0xc0,0x07, //     63 T1 ON, NOTE  64 VOLUME  7
                0x80,0x3e,0x07, //      0 T2 ON, NOTE  62 VOLUME  7
                     0xc0,0x01, //     64 BOTH OFF
                0x81,0xd6,0x07, //      1 T1 ON, NOTE  86 VOLUME  7
                     0xbf,0x01, //     63 BOTH OFF
                0xc1,0xd1,0x05, //     65 T1 ON, NOTE  81 VOLUME  5
                0x80,0x4d,0x05, //      0 T2 ON, NOTE  77 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
           0x01,0x81,0xc1,0x06, //    129 T1 ON, NOTE  65 VOLUME  6
                0xc0,0xc0,0x05, //     64 T1 ON, NOTE  64 VOLUME  5
                0xc0,0xbe,0x05, //     64 T1 ON, NOTE  62 VOLUME  5
                0xc0,0xbc,0x05, //     64 T1 ON, NOTE  60 VOLUME  5
                0xc0,0xbb,0x06, //     64 T1 ON, NOTE  59 VOLUME  6
                0x01,0xcd,0x01, //    205 BOTH OFF
                0xb3,0xca,0x05, //     51 T1 ON, NOTE  74 VOLUME  5
                0x80,0x44,0x05, //      0 T2 ON, NOTE  68 VOLUME  5
                0xbf,0xc0,0x09, //     63 T1 ON, NOTE  64 VOLUME  9
                     0x80,0x00, //      0 T2 OFF
                0xc1,0x47,0x05, //     65 T2 ON, NOTE  71 VOLUME  5
                     0xbf,0x00, //     63 T2 OFF
                0xc1,0xca,0x06, //     65 T1 ON, NOTE  74 VOLUME  6
                0x80,0x44,0x06, //      0 T2 ON, NOTE  68 VOLUME  6
                0xff,0xc0,0x09, //    127 T1 ON, NOTE  64 VOLUME  9
                     0x80,0x00, //      0 T2 OFF
           0x01,0x81,0xc9,0x05, //    129 T1 ON, NOTE  73 VOLUME  5
                0x80,0x45,0x05, //      0 T2 ON, NOTE  69 VOLUME  5
                0xff,0xb9,0x05, //    127 T1 ON, NOTE  57 VOLUME  5
                     0x80,0x00, //      0 T2 OFF
                     0xce,0x01, //     78 BOTH OFF
                0xb3,0xb2,0x05, //     51 T1 ON, NOTE  50 VOLUME  5
           0x02,0x80,0xc8,0x05, //    256 T1 ON, NOTE  72 VOLUME  5
                0x80,0x42,0x05, //      0 T2 ON, NOTE  66 VOLUME  5
                0xbf,0xbe,0x0a, //     63 T1 ON, NOTE  62 VOLUME 10
                     0x80,0x00, //      0 T2 OFF
                0xc1,0x45,0x05, //     65 T2 ON, NOTE  69 VOLUME  5
                     0xbf,0x00, //     63 T2 OFF
                0xc1,0xc8,0x06, //     65 T1 ON, NOTE  72 VOLUME  6
                0x80,0x42,0x06, //      0 T2 ON, NOTE  66 VOLUME  6
                0xff,0xbe,0x0a, //    127 T1 ON, NOTE  62 VOLUME 10
                     0x80,0x00, //      0 T2 OFF
           0x01,0x81,0xc7,0x05, //    129 T1 ON, NOTE  71 VOLUME  5
                0x80,0x43,0x05, //      0 T2 ON, NOTE  67 VOLUME  5
                0xff,0xb7,0x05, //    127 T1 ON, NOTE  55 VOLUME  5
                     0x80,0x00, //      0 T2 OFF
                     0xce,0x01, //     78 BOTH OFF
                0xb3,0xb0,0x05, //     51 T1 ON, NOTE  48 VOLUME  5
           0x02,0x80,0xc6,0x05, //    256 T1 ON, NOTE  70 VOLUME  5
                0x80,0x40,0x05, //      0 T2 ON, NOTE  64 VOLUME  5
                0xbf,0xbc,0x0a, //     63 T1 ON, NOTE  60 VOLUME 10
                     0x80,0x00, //      0 T2 OFF
                0xc1,0x43,0x05, //     65 T2 ON, NOTE  67 VOLUME  5
                     0xbf,0x00, //     63 T2 OFF
                0xc1,0xc6,0x06, //     65 T1 ON, NOTE  70 VOLUME  6
                0x80,0x40,0x06, //      0 T2 ON, NOTE  64 VOLUME  6
                0xff,0xbc,0x0a, //    127 T1 ON, NOTE  60 VOLUME 10
                     0x80,0x00, //      0 T2 OFF
           0x01,0x81,0xc5,0x05, //    129 T1 ON, NOTE  69 VOLUME  5
                0x80,0x41,0x05, //      0 T2 ON, NOTE  65 VOLUME  5
                0xff,0xb5,0x05, //    127 T1 ON, NOTE  53 VOLUME  5
                     0x80,0x00, //      0 T2 OFF
                     0xce,0x01, //     78 BOTH OFF
                0xb3,0xad,0x05, //     51 T1 ON, NOTE  45 VOLUME  5
                     0xff,0x01, //    127 BOTH OFF
                0xa2,0xc5,0x08, //     34 T1 ON, NOTE  69 VOLUME  8
                0xa0,0xc9,0x0a, //     32 T1 ON, NOTE  73 VOLUME 10
                0x94,0xcc,0x0a, //     20 T1 ON, NOTE  76 VOLUME 10
                0xab,0xd1,0x0b, //     43 T1 ON, NOTE  81 VOLUME 11
                0x80,0x37,0x0c, //      0 T2 ON, NOTE  55 VOLUME 12
                0xe5,0xb9,0x0c, //    101 T1 ON, NOTE  57 VOLUME 12
                     0x9a,0x01, //     26 BOTH OFF
           0x01,0x81,0xd6,0x0b, //    129 T1 ON, NOTE  86 VOLUME 11
                0x80,0x39,0x0c, //      0 T2 ON, NOTE  57 VOLUME 12
                     0xff,0x01, //    127 BOTH OFF
                     0x80,0x05  //      0 END PROGRAM
};
