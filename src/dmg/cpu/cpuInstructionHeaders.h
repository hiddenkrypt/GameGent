
#define flagConditional bool
#define CONDITION_ZERO ((bool)(cpuRegisters.f & FLAG_ZERO))
#define CONDITION_NO_ZERO !((bool)(cpuRegisters.f & FLAG_ZERO))
#define CONDITION_CARRY ((bool)(cpuRegisters.f & FLAG_CARRY))
#define CONDITION_NO_CARRY !((bool)(cpuRegisters.f & FLAG_CARRY))
#define CONDITION_SUBTRACT ((bool)(cpuRegisters.f & FLAG_SUBTRACT))
#define CONDITION_HALFCARRY ((bool)(cpuRegisters.f & FLAG_HALFCARRY))
#define CONDITION_ALWAYS (true)


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

typedef enum carryPolicyEnum{
	NO_CARRY = 0,
	WITH_CARRY = 1,
	THROUGH_CARRY = 1
} carryPolicy;

typedef enum significantBitPolicyEnum {
	RESET_SIGNIFICANT_BIT,
	NO_RESET_SIGNIFICANT_BIT
} significantBitPolicy;

typedef enum directionEnum{
	LEFT,
	RIGHT
} direction;

void handleConsistentFlagEffects( instruction opcode );
bool instructionSwitch( uint8_t codePoint );
void prefixInstructionSwitch();

void load_16bitRegister_DirectWord( uint16_t *targetRegister );
void load_8bitRegister_DirectByte( uint8_t *targetRegister );
void load_8bitRegister_MemoryAtRegisterValue( uint8_t *targetRegister, uint16_t address );
void load_8bitRegister_8bitRegister( uint8_t *targetRegister, uint8_t dataRegister );
void load_memory_directByte();
void load_memoryAtRegisterValue_8bitRegisterData( uint16_t address, uint8_t dataRegister );
void load_memoryAtDirectWord_16bitRegister();
void load_memoryAtDirectWord_A();
void load_memoryHighDirectOffset_A();
void load_memoryHighRegisterOffset_A();
void load_A_MemoryAtDirectWord();
void load_A_MemoryHighWithDirectByteOffset();
void load_A_MemoryHighWithRegisterByteOffset();
void increment_16bitRegister( uint16_t *targetRegister );
void decrement_16bitRegister( uint16_t *targetRegister );
void increment_8bitRegister( uint8_t *targetRegister );
void decrement_8bitRegister( uint8_t *targetRegister );
void increment_memoryValue();
void decrement_memoryValue();
void rotate_8bitRegister( uint8_t *targetRegister, direction leftOrRight, carryPolicy throughCarry );
void rotate_memoryByte( direction leftOrRight, carryPolicy throughCarry );
void add_16bitRegister( uint16_t valueRegister );
void accumulator_decimalAdjustment();
void accumulator_complement();
void accumulator_addition( uint8_t value, carryPolicy carryUse );
void accumulator_subtract( uint8_t value, carryPolicy carryUse );
void accumulator_logicalAnd( uint8_t value );
void accumulator_logicalXor( uint8_t value );
void accumulator_logicalOr( uint8_t value );
void accumulator_compare( uint8_t value );
void stack_pop( uint16_t *targetRegister );
void stack_push( uint16_t valueRegister );
void stack_restart( uint8_t address );
void stack_addDirectByteToSP();
void stack_load_HL_SPWithDirectByteOffset();
void stack_load_SP_HL();
void stack_return( flagConditional condition );
void stack_call( flagConditional condition );
bool jump_relativeByte( flagConditional condition );
bool jump_toAddressWord( flagConditional condition );
bool jump_toHL();
void shift( uint8_t *value, direction leftOrRight, significantBitPolicy plan );
void shift_memory( direction leftOrRight, significantBitPolicy plan );
void swapMemoryNibbles();
void swapNibbles( uint8_t *value );
void bit_read( bitmask targetBit, uint8_t *targetByte );
void bit_set( bitmask targetBit, uint8_t *targetByte );
void bit_reset( bitmask targetBit, uint8_t *targetByte );
void bit_memoryRead( bitmask targetBit );
void bit_memoryReset( bitmask targetBit );
void bit_memorySet( bitmask targetBit );
