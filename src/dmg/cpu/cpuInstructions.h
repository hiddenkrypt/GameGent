#pragma once

void executeInstruction( instruction opcode );



typedef enum flagConditionalEnum{
	CONDITION_ZERO,
	CONDITION_CARRY,
	CONDITION_NO_ZERO,
	CONDITION_NO_CARRY,
	CONDITION_ALWAYS
} flagConditional;

typedef enum flagBitmaskEnum {
	FLAG_CARRY = 0x10,
	FLAG_HALFCARRY = 0x20,
	FLAG_SUBTRACT = 0x40,
	FLAG_ZERO = 0x80
} flagBitmask;
