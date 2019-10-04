#include <stdint.h>
#include <stdbool.h>
#pragma once

typedef struct{
    uint8_t codePoint;
    uint8_t argumentsCount;
    uint8_t ticks;
    bool prefixTable;
    char mnemonic[20];
} instruction;

static instruction codeTable[ 0xFF ] = {
    { 0x00, 0, 4, false, "NOP" }
};
static instruction prefixCodeTable[ 0xFF ] = {
    { 0x00,  0, 8, true, "RLC B" }
};
