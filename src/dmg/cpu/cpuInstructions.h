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
void load16Direct( register16 targetRegister );
void load16Direct( register16 targetRegister );
void load8Direct( register8 targetRegister );
void load8Indirect( register16 address, register8 targetRegister );
void increment16( register16 targetRegister );
void increment8( register8 targetRegister );
void decrement8( register8 targetRegister );
void rotateRegister( register8 targetRegister, bool left, bool carry );
void stop();
