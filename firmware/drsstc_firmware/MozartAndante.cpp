#include "MIDIPlayer.h"

// converted from mozart.mid - 46 bytes total
extern const byte MOZART_ANDANTE[] PROGMEM = 
{
           0xf8,0x26,0x46,0x9b, //      0 BEGIN PROGRAM (120 ticks/beat, tempo = 631579 us/beat)
                0x80,0xc8,0x0a, //      0 T1 ON, NOTE  72 VOLUME 10
                0x80,0x39,0x0a, //      0 T2 ON, NOTE  57 VOLUME 10
                0xbb,0x48,0x00, //     59 T2 ON, NOTE  72 VOLUME  0
                0x81,0xcc,0x0a, //      1 T1 ON, NOTE  76 VOLUME 10
                0xbb,0x4c,0x00, //     59 T2 ON, NOTE  76 VOLUME  0
                0xa8,0xcd,0x0a, //     40 T1 ON, NOTE  77 VOLUME 10
                0xa7,0x4d,0x00, //     39 T2 ON, NOTE  77 VOLUME  0
                0x81,0xcf,0x0a, //      1 T1 ON, NOTE  79 VOLUME 10
                0xa7,0x4f,0x00, //     39 T2 ON, NOTE  79 VOLUME  0
                0x81,0xd1,0x0a, //      1 T1 ON, NOTE  81 VOLUME 10
                0xa7,0x51,0x00, //     39 T2 ON, NOTE  81 VOLUME  0
           0x01,0xb5,0xd4,0x0a, //    181 T1 ON, NOTE  84 VOLUME 10
                0xbb,0x54,0x00, //     59 T2 ON, NOTE  84 VOLUME  0
                     0x80,0x05  //      0 END PROGRAM
};
