#pragma once

#include "instructionStructure.h"
void executeInstruction( instruction opcode );



typedef enum flagBitmaskEnum {
	FLAG_CARRY = 0x10,
	FLAG_HALFCARRY = 0x20,
	FLAG_SUBTRACT = 0x40,
	FLAG_ZERO = 0x80
} flagBitmask;
