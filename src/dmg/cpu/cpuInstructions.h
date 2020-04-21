#pragma once

void executeInstruction( instruction opcode );



typedef enum flagBitmaskEnum {
	FLAG_CARRY = 0x10,
	FLAG_HALFCARRY = 0x20,
	FLAG_SUBTRACT = 0x40,
	FLAG_ZERO = 0x80
} flagBitmask;

typedef enum bitSelectionEnum {
	BIT_ZERO = 0x01,
	BIT_ONE = 0x02,
	BIT_TWO = 0x04,
	BIT_THREE = 0x08,
	BIT_FOUR = 0x10,
	BIT_FIVE = 0x20,
	BIT_SIX = 0x40,
	BIT_SEVEN = 0x80
} bitmask;
