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

static instruction codeTable[ 0xFF ] = {
  { 0x00, 1, 4,   4, {NO_FLAGS}, "NOP", "",  "" },
  { 0x01, 3, 12, 12, {NO_FLAGS}, "LD", "BC", "d16" },
  { 0x02, 1, 8,   8, {NO_FLAGS}, "LD", "(BC)", "A" },
  { 0x03, 1, 8,   8, {NO_FLAGS}, "INC", "BC" },
  { 0x04, 1, 4,   4, {E_APPLIED, E_CLEARED, E_APPLIED, E_UNAFFECTED}, "INC", "B", "" },
  { 0x05, 1, 4,   4, {E_APPLIED, E_RAISED, E_APPLIED, E_UNAFFECTED}, "DEC", "B", "" },
  { 0x06, 2, 8,   8, {NO_FLAGS}, "LD", "B", "d8" },
  { 0x07, 1, 4,   4, {E_CLEARED,E_CLEARED,E_CLEARED,E_APPLIED}, "RLCA", "", ""  },
  { 0x08, 3, 20, 20, {NO_FLAGS}, "LD", "(a16)", "SP" },
  { 0x09, 1, 8,   8, {E_UNAFFECTED, E_CLEARED, E_APPLIED, E_APPLIED}, "ADD","HL", "BC" },
  { 0x0a, 1, 8,   8, {NO_FLAGS}, "LD", "A", "(BC)" },
  { 0x0b, 1, 8,   8, {NO_FLAGS}, "DEC", "BC", "" },
  { 0x0c, 1, 4,   4, {E_APPLIED, E_CLEARED, E_APPLIED, E_UNAFFECTED}, "INC", "C", "" },
  { 0x0d, 1, 4,   4, {E_APPLIED, E_RAISED, E_APPLIED, E_UNAFFECTED}, "DEC", "C", "" },
  { 0x0e, 2, 8,   8, {NO_FLAGS}, "LD", "C", "d8" },
  { 0x0f, 1, 4,   4, {E_CLEARED,E_CLEARED,E_CLEARED,E_APPLIED}, "RRCA", "", "" }
};
static instruction prefixCodeTable[ 0xFF ] = {
    { 0x00,  0, 8, {E_APPLIED, E_CLEARED, E_CLEARED, E_APPLIED}, "RLC B" }
};
