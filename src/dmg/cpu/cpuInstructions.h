#pragma once

void executeInstruction( instruction opcode );

typedef enum register8Enum{
	A,
	B,
	C,
	D,
	E,
	F,
	H,
	L
} register8;
typedef enum register16Enum{
	PC,
	SP,
	AF,
	BC,
	DE,
	HL
} register16;

typedef enum flagConditionalEnum{
	CONDITION_ZERO,
	CONDITION_CARRY,
	CONDITION_NO_ZERO,
	CONDITION_NO_CARRY,
	CONDITION_ALWAYS
} flagConditional;
