#include <stdint.h>
#include <stdbool.h>
#pragma once
#define NO_FLAGS {UNAFFECTED,UNAFFECTED,UNAFFECTED,UNAFFECTED}
typedef enum flagEffectEnum{
    UNAFFECTED = 0,
    FLAG_CLEARED = 1,
    FLAG_RAISED = 2,
    FLAG_APPLIED = 3
} flagEffect;

typedef struct{
    flagEffect zero;
    flagEffect sub;
    flagEffect halfcarry;
    flagEffect carry;
} flagEffects;


typedef struct{
    uint8_t codePoint;
    uint8_t argumentsCount;
    uint8_t ticks;
    flagEffects flags;
    char mnemonic[20];
} instruction;

static instruction codeTable[ 0xFF ] = {
    { 0x00, 0, 4, NO_FLAGS, "NOP" },
    { 0x01, 2, 12, NO_FLAGS, "LD BC, d16" }
};
static instruction prefixCodeTable[ 0xFF ] = {
    { 0x00,  0, 8, {FLAG_APPLIED, FLAG_CLEARED, FLAG_CLEARED, FLAG_APPLIED}, "RLC B" }
};
