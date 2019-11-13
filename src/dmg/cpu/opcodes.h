#pragma once
#include <stdint.h>
#include <stdbool.h>
#define NO_FLAGS E_UNAFFECTED,E_UNAFFECTED,E_UNAFFECTED,E_UNAFFECTED
typedef enum flagEffectEnum{
    E_UNAFFECTED = 0,
    E_CLEARED = 1,
    E_RAISED = 2,
    E_APPLIED = 3
} flagEffect;

typedef struct{
    flagEffect zero;
    flagEffect subtract;
    flagEffect halfCarry;
    flagEffect carry;
} flagEffects;


typedef struct{
    uint8_t codePoint;
    uint8_t length;
    uint8_t cycles;
    uint8_t cyclesAbort;
    flagEffects flags;
    char mnemonic[6];
    char arg1[5];
    char arg2[5];
} instruction;

#include "codeTables.h"
