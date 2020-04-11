#define NO_CARRY false
#define WITH_CARRY true
#define THROUGH_CARRY true
#define LEFT true
#define RIGHT false

#define flagConditional bool
#define CONDITION_ZERO ((bool)cpuRegisters.f & FLAG_ZERO)
#define CONDITION_NO_ZERO !((bool)cpuRegisters.f & FLAG_ZERO)
#define CONDITION_CARRY ((bool)cpuRegisters.f & FLAG_CARRY)
#define CONDITION_NO_CARRY !((bool)cpuRegisters.f & FLAG_CARRY)
#define CONDITION_SUBTRACT ((bool)cpuRegisters.f & FLAG_SUBTRACT)
#define CONDITION_HALFCARRY ((bool)cpuRegisters.f & FLAG_HALFCARRY)
#define CONDITION_ALWAYS (true)

void handleStaticFlagEffects( instruction opcode );
void instructionSwitch( uint8_t codePoint );
void prefixInstructionSwitch();

void load_16bitRegister_DirectWord( uint16_t* targetRegister );
void load_8bitRegister_DirectByte( uint8_t* targetRegister );
void load_8bitRegister_MemoryAtRegisterValue( uint8_t* targetRegister, uint16_t address );
void load_8bitRegister_8bitRegister( uint8_t* targetRegister, uint8_t dataRegister );
void load_memory_directByte();
void load_memoryAtRegisterValue_8bitRegisterData( uint16_t address, uint8_t dataRegister );
void load_memoryAtDirectWord_16bitRegister();
void load_memoryAtDirectWord_A();
void load_memoryHighDirectOffset_A();
void load_memoryHighRegisterOffset_A();
void load_A_MemoryAtDirectWord();
void load_A_MemoryHighWithDirectByteOffset();
void load_A_MemoryHighWithRegisterByteOffset();
void increment_16bitRegister( uint16_t* targetRegister );
void decrement_16bitRegister( uint16_t* targetRegister );
void increment_8bitRegister( uint8_t* targetRegister );
void decrement_8bitRegister( uint8_t* targetRegister );
void increment_memoryValue();
void decrement_memoryValue();
void rotate_8bitRegister( uint8_t* targetRegister, bool left, bool throughCarry );
void rotate_memoryByte( bool left, bool throughCarry );
void add_16bitRegister( uint16_t valueRegister );
void accumulator_decimalAdjustment();
void accumulator_complement();
void accumulator_addition( uint8_t value, bool useCarry );
void accumulator_subtract( uint8_t value, bool useCarry );
void accumulator_logicalAnd( uint8_t value );
void accumulator_logicalXor( uint8_t value );
void accumulator_logicalOr( uint8_t value );
void accumulator_compare( uint8_t value );
void stack_pop( uint16_t* targetRegister );
void stack_push( uint16_t valueRegister );
void stack_restart( uint8_t address );
void stack_addDirectByteToSP();
void stack_load_HL_SPWithDirectByteOffset();
void stack_load_SP_HL();
void stack_return( flagConditional condition );
void stack_call( flagConditional condition );
void jump_relativeByte( flagConditional condition );
void jump_toAddressWord( flagConditional condition );
void jump_toHL();
