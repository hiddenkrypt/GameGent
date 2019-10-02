#pragma once
#include <stdint.h>

#define FLAG_ZERO 0x80
#define FLAG_ADDSUM 0x40
#define FLAG_HALFCARRY 0x20
#define FLAG_CARRY 0x10


typedef struct {
    struct{
        union{
            struct{
                uint8_t f;
                uint8_t a;
            };
            uint16_t af;
        };
    };
        struct{
        union{
            struct{
                uint8_t c;
                uint8_t b;
            };
            uint16_t bc;
        };
    };
        struct{
        union{
            struct{
                uint8_t e;
                uint8_t d;
            };
            uint16_t de;
        };
    };
        struct{
        union{
            struct{
                uint8_t l;
                uint8_t h;
            };
            uint16_t hl;
        };
    };
    uint16_t SP;
    uint16_t PC;
} DmgRegisters;
