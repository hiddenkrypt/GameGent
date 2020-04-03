#include <stdio.h>
#include "registers.h"
#include "opcodes.h"
#include "../mmu/mmu.h"
#include "cpuInstructions.h"

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


/** @todo fix overflows from math ops
 * @todo set flags
 * @todo figure out branch timing
 */
void cpu_noop(){}
void cpu_stop(){}
void cpu_halt(){}
void cpu_setCarryFlag(){
	cpuRegisters.f = cpuRegisters.f | FLAG_CARRY;
}
void cpu_clearCarryFlag(){
	cpuRegisters.f = cpuRegisters.f & (~FLAG_CARRY);
}
void cpu_flipCarryFlag(){
	cpuRegisters.f = cpuRegisters.f ^ FLAG_CARRY;
}
bool cpu_getCarryFlag(){
	return cpuRegisters.f & FLAG_CARRY;
}



void cpu_setZeroFlag(){
	cpuRegisters.f = cpuRegisters.f | FLAG_ZERO;
}
void cpu_clearZeroFlag(){
	cpuRegisters.f = cpuRegisters.f & (~FLAG_ZERO);
}
bool cpu_getZeroFlag(){
	return cpuRegisters.f & FLAG_ZERO;
}



void cpu_setHalfCarryFlag(){
	cpuRegisters.f = cpuRegisters.f | FLAG_HALFCARRY;
}
void cpu_clearHalfCarryFlag(){
	cpuRegisters.f = cpuRegisters.f & (~FLAG_HALFCARRY);
}
bool cpu_getHalfCarryFlag(){
	return cpuRegisters.f & FLAG_HALFCARRY;
}



void cpu_setSubtractFlag(){
	cpuRegisters.f = cpuRegisters.f | FLAG_SUBTRACT;
}
void cpu_clearSubtractFlag(){
	cpuRegisters.f = cpuRegisters.f & (~FLAG_SUBTRACT);
}
bool cpu_getSubtractFlag(){
	return cpuRegisters.f & FLAG_SUBTRACT;
}



void cpu_enableInterrupts(){
	cpuRegisters.ime = true;
}
void cpu_disableInterrupts(){
	cpuRegisters.ime = false;
}

void load_16bitRegister_DirectWord( uint16_t* targetRegister ){
	*targetRegister = MMU_readWord( cpuRegisters.pc + 1 );
}
void load_8bitRegister_DirectByte( uint8_t* targetRegister ){
	*targetRegister = MMU_readWord( cpuRegisters.pc + 1 );
}
void load_8bitRegister_MemoryAtRegisterValue( uint8_t* targetRegister, uint16_t address ){
	*targetRegister = MMU_readWord( address );
}
void load_8bitRegister_8bitRegister( uint8_t* targetRegister, uint8_t dataRegister ){
	*targetRegister = dataRegister;
}
void load_memory_directByte(){
	MMU_loadByte( cpuRegisters.hl, MMU_readByte( cpuRegisters.pc + 1 ) );
}
void load_memoryAtRegisterValue_8bitRegisterData( uint16_t address, uint8_t dataRegister ){
	MMU_loadByte( address, dataRegister );
}
void load_memoryAtDirectWord_16bitRegister(){
	MMU_loadWord( MMU_readWord( cpuRegisters.pc + 1 ), cpuRegisters.sp );
}
void load_memoryAtDirectWord_A(){
	MMU_loadByte( MMU_readWord( cpuRegisters.pc + 1 ), cpuRegisters.a );
}
void load_memoryHighDirectOffset_A(){
	MMU_loadByte( 0xff00 + MMU_readByte( cpuRegisters.pc + 1 ), cpuRegisters.a );
}
void load_memoryHighRegisterOffset_A(){
	MMU_loadByte( 0xff00 + cpuRegisters.c, cpuRegisters.a );
}
void load_A_MemoryAtDirectWord(){
	cpuRegisters.a = MMU_readByte( cpuRegisters.pc + 1 );
}
void load_A_MemoryHighWithDirectByteOffset(){
	cpuRegisters.a = MMU_readByte( 0xff00 + MMU_readByte( cpuRegisters.pc + 1 ) );
}
void load_A_MemoryHighWithRegisterByteOffset(){
	cpuRegisters.a = MMU_readByte( 0xff00 + cpuRegisters.c );
}

void increment_16bitRegister( uint16_t* targetRegister ){
	*targetRegister = *targetRegister+1;
}
void decrement_16bitRegister( uint16_t* targetRegister ){
	*targetRegister = *targetRegister-1;
}
void increment_8bitRegister( uint8_t* targetRegister ){
	if( !( *targetRegister & 0x0F ) ) {
		cpu_setHalfCarryFlag();
	}
	*targetRegister = *targetRegister + 1;
	if( *targetRegister == 0 ){
		cpu_setZeroFlag();
	}
	if( !( *targetRegister & 0x0F ) ) {
		cpu_setHalfCarryFlag();
	}
}
void decrement_8bitRegister( uint8_t* targetRegister ){
	*targetRegister = *targetRegister-1;
	if( ( *targetRegister & 0x0f ) == 0x0f ){
		cpu_setHalfCarryFlag();
	}
	if( *targetRegister == 0 ){
		cpu_setZeroFlag();
	}
}
void increment_memoryValue(){
	MMU_loadByte( cpuRegisters.hl, MMU_readByte( cpuRegisters.hl ) + 1 );
	if( MMU_readByte( cpuRegisters.hl ) == 0 ){
		cpu_setZeroFlag();
	}
	if( !( MMU_readByte( cpuRegisters.hl ) & 0x0F ) ) {
		cpu_setHalfCarryFlag();
	}
}
void decrement_memoryValue(){
	MMU_loadByte( cpuRegisters.hl, MMU_readByte( cpuRegisters.hl ) - 1 );
	if( MMU_readByte( cpuRegisters.hl ) == 0 ){
		cpu_setZeroFlag();
	}
	if( ( MMU_readByte( cpuRegisters.hl ) & 0x0f ) == 0x0f ){
		cpu_setHalfCarryFlag();
	}
}

void rotate_8bitRegister( uint8_t* targetRegister, bool left, bool throughCarry ){
	if( left ){
		uint8_t msb = *targetRegister >> 7;
		*targetRegister = *targetRegister << 1;
		if( throughCarry ){
			uint8_t previousCarry = cpu_getCarryFlag();
			if( msb ){
				cpu_setCarryFlag();
			} else {
				cpu_clearCarryFlag();
			}
			if( previousCarry ){
				*targetRegister = *targetRegister | 0x01;
			} else {
				*targetRegister = *targetRegister & 0xfe;
			}
		} else {
			if( msb ){
				cpu_setCarryFlag();
				*targetRegister = *targetRegister | 0x01;
			} else {
				cpu_clearCarryFlag();
				*targetRegister = *targetRegister & 0xfe;
			}
		}
	} else {
		uint8_t lsb = *targetRegister & 0x01;
		*targetRegister = *targetRegister >> 1;
		if( throughCarry ){
			uint8_t previousCarry = cpu_getCarryFlag();
			if( lsb ){
				cpu_setCarryFlag();
			} else {
				cpu_clearCarryFlag();
			}
			if( previousCarry ){
				*targetRegister = *targetRegister | 0x80;
			} else {
				*targetRegister = *targetRegister & 0x7f;
			}
		} else {
			if( lsb ){
				cpu_setCarryFlag();
				*targetRegister = *targetRegister | 0x80;
			} else {
				cpu_clearCarryFlag();
				*targetRegister = *targetRegister & 0x7f;
			}
		}
	}
	if( *targetRegister == 0 ){
		cpu_setZeroFlag();
	}
}

void add_16bitRegister( uint16_t valueRegister ){
	if( ( ( cpuRegisters.hl & 0x0fff ) + ( valueRegister & 0x0fff ) ) &0x1000 ){
		cpu_setHalfCarryFlag();
	}
	cpuRegisters.hl = cpuRegisters.hl + valueRegister;
	if( cpuRegisters.hl < valueRegister ){
		cpu_setCarryFlag();
	}
}

void accumulator_add_8bitRegister( uint8_t valueRegister, bool useCarry ){
	cpuRegisters.a = cpuRegisters.a + valueRegister;
	if( useCarry ){
		cpuRegisters.a = cpuRegisters.a + cpu_getCarryFlag();
	}
	if( cpuRegisters.a < valueRegister ){
		cpu_setCarryFlag();
	}
}
void accumulator_add_memoryValue( bool useCarry ){
	cpuRegisters.a = cpuRegisters.a + MMU_readByte( cpuRegisters.hl );
	if( useCarry ){
		cpuRegisters.a = cpuRegisters.a + cpu_getCarryFlag();
	}
}
void accumulator_add_directByte( bool useCarry ){
	cpuRegisters.a = cpuRegisters.a + MMU_readByte( cpuRegisters.pc+1 );
	if( useCarry ){
		cpuRegisters.a = cpuRegisters.a + cpu_getCarryFlag();
	}
	if( cpuRegisters.a <  MMU_readByte( cpuRegisters.pc+1 ) ){
		cpu_setCarryFlag();
	} else {
		cpu_clearCarryFlag();
	}
}
void accumulator_decimalAdjustment(){
	uint16_t workingValue = cpuRegisters.a;
	if ( CONDITION_SUBTRACT ){
		if( CONDITION_HALFCARRY ){
			workingValue = ( workingValue - 0x06 ) & 0xff ;
		}
		if( CONDITION_CARRY ){
			workingValue = workingValue - 0x60;
		}
	} else {
		if( CONDITION_HALFCARRY || ( workingValue & 0x0f ) > 9 ){
			workingValue = workingValue + 0x06;
		}
		if( CONDITION_CARRY || workingValue > 0x9f){
			workingValue = workingValue + 0x60;
		}
	}
	if( workingValue >= 0x100 ){
		cpu_setCarryFlag();
	}
	cpuRegisters.a = workingValue & 0xff;
}
void accumulator_complement(){
	cpuRegisters.a = ~cpuRegisters.a;
}
void accumulator_sub_memoryValue( bool carry ){}
void accumulator_sub_8bitRegister( uint8_t valueRegister, bool carry ){}
void accumulator_sub_directByte(){}
void accumulator_and_8bitRegister( uint8_t valueRegister ){}
void accumulator_and_memoryValue(){}
void accumulator_and_directByte(){}
void accumulator_xor_8bitRegister( uint8_t valueRegister ){}
void accumulator_xor_memoryValue(){}
void accumulator_xor_directByte(){}
void accumulator_or_8bitRegister( uint8_t valueRegister ){}
void accumulator_or_memoryValue(){}
void accumulator_or_directByte(){}
void accumulator_cp_8bitRegister( uint8_t valueRegister ){}
void accumulator_cp_memoryValue(){}
void accumulator_cp_directByte(){}

void stack_pop( uint16_t* targetRegister ){}
void stack_push( uint16_t valueRegister ){}
void stack_reset( uint8_t offset ){}
void stack_addDirectByteToSP(){}
void stack_load_HL_SPWithDirectByteOffset(){}
void stack_load_SP_HL(){}
void stack_return( flagConditional condition ){}
void stack_call( flagConditional condition ){}

void jump_relativeByte( flagConditional condition ){}
void jump_toAddressWord( flagConditional condition ){}
void jump_toHL(){}

void cpu_prefix(){}


inline void executeInstruction( instruction opcode ){
	printf("called for %#04x %s\n", opcode.codePoint, opcode.mnemonic);
	switch( opcode.codePoint ){
		case 0x00:
			cpu_noop();
			break;
		case 0x01:
			load_16bitRegister_DirectWord( &cpuRegisters.bc );
			break;
		case 0x02:
			load_memoryAtRegisterValue_8bitRegisterData( cpuRegisters.bc, cpuRegisters.a );
			break;
		case 0x03:
			increment_16bitRegister( &cpuRegisters.bc );
			break;
		case 0x04:
			increment_8bitRegister( &cpuRegisters.b );
			break;
		case 0x05:
			decrement_8bitRegister( &cpuRegisters.b );
			break;
		case 0x06:
			load_8bitRegister_DirectByte( &cpuRegisters.b );
			break;
		case 0x07:
			rotate_8bitRegister( &cpuRegisters.a, LEFT, NO_CARRY);
			break;
		case 0x08:
			load_memoryAtDirectWord_16bitRegister(); //add sp
			break;
		case 0x09:
			add_16bitRegister( cpuRegisters.bc );
			break;
		case 0x0a:
			load_8bitRegister_MemoryAtRegisterValue( &cpuRegisters.a, cpuRegisters.bc );
			break;
		case 0x0b:
			decrement_16bitRegister( &cpuRegisters.bc );
			break;
		case 0x0c:
			increment_8bitRegister( &cpuRegisters.c );
			break;
		case 0x0d:
			decrement_8bitRegister( &cpuRegisters.c );
			break;
		case 0x0e:
			load_8bitRegister_DirectByte( &cpuRegisters.c );
			break;
		case 0x0f:
			rotate_8bitRegister( &cpuRegisters.a, RIGHT, NO_CARRY );
			break;
		case 0x10:
			cpu_stop();
			break;
		case 0x11:
			load_16bitRegister_DirectWord( &cpuRegisters.de );
			break;
		case 0x12:
			load_memoryAtRegisterValue_8bitRegisterData( cpuRegisters.de, cpuRegisters.a );
			break;
		case 0x13:
			increment_16bitRegister( &cpuRegisters.de );
			break;
		case 0x14:
			increment_8bitRegister( &cpuRegisters.d );
			break;
		case 0x15:
			decrement_8bitRegister( &cpuRegisters.d );
			break;
		case 0x16:
			load_8bitRegister_DirectByte( &cpuRegisters.d );
			break;
		case 0x17:
			rotate_8bitRegister( &cpuRegisters.a, LEFT, THROUGH_CARRY );
			break;
		case 0x18:
			jump_relativeByte( CONDITION_ALWAYS );
			break;
		case 0x19:
			add_16bitRegister( cpuRegisters.de );
			break;
		case 0x1a:
			load_8bitRegister_MemoryAtRegisterValue( &cpuRegisters.a, cpuRegisters.de );
			break;
		case 0x1b:
			decrement_16bitRegister( &cpuRegisters.de );
			break;
		case 0x1c:
			increment_8bitRegister( &cpuRegisters.e );
			break;
		case 0x1d:
			decrement_8bitRegister( &cpuRegisters.e );
			break;
		case 0x1e:
			load_8bitRegister_DirectByte( &cpuRegisters.e );
			break;
		case 0x1f:
			rotate_8bitRegister( &cpuRegisters.a, RIGHT, THROUGH_CARRY );
			break;
		case 0x20:
			jump_relativeByte( CONDITION_NO_ZERO );
			break;
		case 0x21:
			load_16bitRegister_DirectWord( &cpuRegisters.hl );
			break;
		case 0x22:
			load_memoryAtRegisterValue_8bitRegisterData( cpuRegisters.hl, cpuRegisters.a );
			increment_16bitRegister( &cpuRegisters.hl );
			break;
		case 0x23:
			increment_16bitRegister( &cpuRegisters.hl );
			break;
		case 0x24:
			increment_8bitRegister( &cpuRegisters.h );
			break;
		case 0x25:
			decrement_8bitRegister( &cpuRegisters.h );
			break;
		case 0x26:
			load_8bitRegister_DirectByte( &cpuRegisters.h );
			break;
		case 0x27:
			accumulator_decimalAdjustment();
			break;
		case 0x28:
			jump_relativeByte( CONDITION_ZERO );
			break;
		case 0x29:
			add_16bitRegister( cpuRegisters.hl );
			break;
		case 0x2a:
			load_8bitRegister_MemoryAtRegisterValue( &cpuRegisters.a, cpuRegisters.hl );
			increment_16bitRegister( &cpuRegisters.hl );
			break;
		case 0x2b:
			decrement_16bitRegister( &cpuRegisters.hl );
			break;
		case 0x2c:
			increment_8bitRegister( &cpuRegisters.l );
			break;
		case 0x2d:
			decrement_8bitRegister( &cpuRegisters.l );
			break;
		case 0x2e:
			load_8bitRegister_DirectByte( &cpuRegisters.l );
			break;
		case 0x2f:
			accumulator_complement();
			break;
		case 0x30:
			jump_relativeByte( CONDITION_NO_CARRY );
			break;
		case 0x31:
			load_16bitRegister_DirectWord( &cpuRegisters.sp );
			break;
		case 0x32:
			load_memoryAtRegisterValue_8bitRegisterData( cpuRegisters.hl, cpuRegisters.a );
			decrement_16bitRegister( &cpuRegisters.hl );
			break;
		case 0x33:
			increment_16bitRegister( &cpuRegisters.sp );
			break;
		case 0x34:
			increment_memoryValue();
			break;
		case 0x35:
			decrement_memoryValue();
			break;
		case 0x36:
			load_memory_directByte();
			break;
		case 0x37:
			cpu_setCarryFlag();
			break;
		case 0x38:
			jump_relativeByte( CONDITION_CARRY );
			break;
		case 0x39:
			add_16bitRegister( cpuRegisters.sp );
			break;
		case 0x3a:
			load_8bitRegister_MemoryAtRegisterValue( &cpuRegisters.a, cpuRegisters.hl );
			decrement_16bitRegister( &cpuRegisters.hl );
			break;
		case 0x3b:
			decrement_16bitRegister( &cpuRegisters.sp );
			break;
		case 0x3c:
			increment_8bitRegister( &cpuRegisters.a );
			break;
		case 0x3d:
			decrement_8bitRegister( &cpuRegisters.a );
			break;
		case 0x3e:
			load_8bitRegister_DirectByte( &cpuRegisters.a );
			break;
		case 0x3f:
			cpu_flipCarryFlag();
			break;
		case 0x40:
			cpu_noop();
			break;
		case 0x41:
			load_8bitRegister_8bitRegister( &cpuRegisters.b, cpuRegisters.c );
			break;
		case 0x42:
			load_8bitRegister_8bitRegister( &cpuRegisters.b, cpuRegisters.d );
			break;
		case 0x43:
			load_8bitRegister_8bitRegister( &cpuRegisters.b, cpuRegisters.e );
			break;
		case 0x44:
			load_8bitRegister_8bitRegister( &cpuRegisters.b, cpuRegisters.h );
			break;
		case 0x45:
			load_8bitRegister_8bitRegister( &cpuRegisters.b, cpuRegisters.l );
			break;
		case 0x46:
			load_8bitRegister_MemoryAtRegisterValue( &cpuRegisters.b, cpuRegisters.hl );
			break;
		case 0x47:
			load_8bitRegister_8bitRegister( &cpuRegisters.b, cpuRegisters.a );
			break;
		case 0x48:
			load_8bitRegister_8bitRegister( &cpuRegisters.c, cpuRegisters.b );
			break;
		case 0x49:
			cpu_noop();
			break;
		case 0x4a:
			load_8bitRegister_8bitRegister( &cpuRegisters.c, cpuRegisters.d );
			break;
		case 0x4b:
			load_8bitRegister_8bitRegister( &cpuRegisters.c, cpuRegisters.e );
			break;
		case 0x4c:
			load_8bitRegister_8bitRegister( &cpuRegisters.c, cpuRegisters.h );
			break;
		case 0x4d:
			load_8bitRegister_8bitRegister( &cpuRegisters.c, cpuRegisters.l );
			break;
		case 0x4e:
			load_8bitRegister_MemoryAtRegisterValue( &cpuRegisters.c, cpuRegisters.hl );
			break;
		case 0x4f:
			load_8bitRegister_8bitRegister( &cpuRegisters.c, cpuRegisters.a );
			break;
		case 0x50:
			load_8bitRegister_8bitRegister( &cpuRegisters.d, cpuRegisters.b );
			break;
		case 0x51:
			load_8bitRegister_8bitRegister( &cpuRegisters.d, cpuRegisters.c );
			break;
		case 0x52:
			cpu_noop();
			break;
		case 0x53:
			load_8bitRegister_8bitRegister( &cpuRegisters.d, cpuRegisters.e );
			break;
		case 0x54:
			load_8bitRegister_8bitRegister( &cpuRegisters.d, cpuRegisters.h );
			break;
		case 0x55:
			load_8bitRegister_8bitRegister( &cpuRegisters.d, cpuRegisters.l );
			break;
		case 0x56:
			load_8bitRegister_MemoryAtRegisterValue( &cpuRegisters.d, cpuRegisters.hl );
			break;
		case 0x57:
			load_8bitRegister_8bitRegister( &cpuRegisters.d, cpuRegisters.a );
			break;
		case 0x58:
			load_8bitRegister_8bitRegister( &cpuRegisters.e, cpuRegisters.b );
			break;
		case 0x59:
			load_8bitRegister_8bitRegister( &cpuRegisters.e, cpuRegisters.c );
			break;
		case 0x5a:
			load_8bitRegister_8bitRegister( &cpuRegisters.e, cpuRegisters.d );
			break;
		case 0x5b:
			cpu_noop();
			break;
		case 0x5c:
			load_8bitRegister_8bitRegister( &cpuRegisters.e, cpuRegisters.h );
			break;
		case 0x5d:
			load_8bitRegister_8bitRegister( &cpuRegisters.e, cpuRegisters.l );
			break;
		case 0x5e:
			load_8bitRegister_MemoryAtRegisterValue( &cpuRegisters.e, cpuRegisters.hl );
			break;
		case 0x5f:
			load_8bitRegister_8bitRegister( &cpuRegisters.e, cpuRegisters.a );
			break;
		case 0x60:
			load_8bitRegister_8bitRegister( &cpuRegisters.h, cpuRegisters.b );
			break;
		case 0x61:
			load_8bitRegister_8bitRegister( &cpuRegisters.h, cpuRegisters.c );
			break;
		case 0x62:
			load_8bitRegister_8bitRegister( &cpuRegisters.h, cpuRegisters.d );
			break;
		case 0x63:
			load_8bitRegister_8bitRegister( &cpuRegisters.h, cpuRegisters.e );
			break;
		case 0x64:
			cpu_noop();
			break;
		case 0x65:
			load_8bitRegister_8bitRegister( &cpuRegisters.h, cpuRegisters.l );
			break;
		case 0x66:
			load_8bitRegister_MemoryAtRegisterValue( &cpuRegisters.h, cpuRegisters.hl );
			break;
		case 0x67:
			load_8bitRegister_8bitRegister( &cpuRegisters.h, cpuRegisters.a );
			break;
		case 0x68:
			load_8bitRegister_8bitRegister( &cpuRegisters.l, cpuRegisters.b );
			break;
		case 0x69:
			load_8bitRegister_8bitRegister( &cpuRegisters.l, cpuRegisters.c );
			break;
		case 0x6a:
			load_8bitRegister_8bitRegister( &cpuRegisters.l, cpuRegisters.d );
			break;
		case 0x6b:
			load_8bitRegister_8bitRegister( &cpuRegisters.l, cpuRegisters.e );
			break;
		case 0x6c:
			load_8bitRegister_8bitRegister( &cpuRegisters.l, cpuRegisters.h );
			break;
		case 0x6d:
			cpu_noop();
			break;
		case 0x6e:
			load_8bitRegister_MemoryAtRegisterValue( &cpuRegisters.l, cpuRegisters.hl );
			break;
		case 0x6f:
			load_8bitRegister_8bitRegister( &cpuRegisters.l, cpuRegisters.a );
			break;
		case 0x70:
			load_memoryAtRegisterValue_8bitRegisterData( cpuRegisters.hl, cpuRegisters.b );
			break;
		case 0x71:
			load_memoryAtRegisterValue_8bitRegisterData( cpuRegisters.hl, cpuRegisters.c );
			break;
		case 0x72:
			load_memoryAtRegisterValue_8bitRegisterData( cpuRegisters.hl, cpuRegisters.d );
			break;
		case 0x73:
			load_memoryAtRegisterValue_8bitRegisterData( cpuRegisters.hl, cpuRegisters.e );
			break;
		case 0x74:
			load_memoryAtRegisterValue_8bitRegisterData( cpuRegisters.hl, cpuRegisters.h );
			break;
		case 0x75:
			load_memoryAtRegisterValue_8bitRegisterData( cpuRegisters.hl, cpuRegisters.l );
			break;
		case 0x76:
			cpu_halt();
			break;
		case 0x77:
			load_memoryAtRegisterValue_8bitRegisterData( cpuRegisters.hl, cpuRegisters.a );
			break;
		case 0x78:
			load_8bitRegister_8bitRegister( &cpuRegisters.a, cpuRegisters.b );
			break;
		case 0x79:
			load_8bitRegister_8bitRegister( &cpuRegisters.a, cpuRegisters.c );
			break;
		case 0x7a:
			load_8bitRegister_8bitRegister( &cpuRegisters.a, cpuRegisters.d );
			break;
		case 0x7b:
			load_8bitRegister_8bitRegister( &cpuRegisters.a, cpuRegisters.e );
			break;
		case 0x7c:
			load_8bitRegister_8bitRegister( &cpuRegisters.a, cpuRegisters.h );
			break;
		case 0x7d:
			load_8bitRegister_8bitRegister( &cpuRegisters.a, cpuRegisters.l );
			break;
		case 0x7e:
			load_8bitRegister_MemoryAtRegisterValue( &cpuRegisters.a, cpuRegisters.hl );
			break;
		case 0x7f:
			cpu_noop();
			break;
		case 0x80:
			accumulator_add_8bitRegister( cpuRegisters.b, NO_CARRY );
			break;
		case 0x81:
			accumulator_add_8bitRegister( cpuRegisters.c, NO_CARRY );
			break;
		case 0x82:
			accumulator_add_8bitRegister( cpuRegisters.d, NO_CARRY );
			break;
		case 0x83:
			accumulator_add_8bitRegister( cpuRegisters.e, NO_CARRY );
			break;
		case 0x84:
			accumulator_add_8bitRegister( cpuRegisters.h, NO_CARRY );
			break;
		case 0x85:
			accumulator_add_8bitRegister( cpuRegisters.l, NO_CARRY );
			break;
		case 0x86:
			accumulator_add_memoryValue( NO_CARRY );
			break;
		case 0x87:
			accumulator_add_8bitRegister( cpuRegisters.a, NO_CARRY );
			break;
		case 0x88:
			accumulator_add_8bitRegister( cpuRegisters.b, WITH_CARRY );
			break;
		case 0x89:
			accumulator_add_8bitRegister( cpuRegisters.c, WITH_CARRY );
			break;
		case 0x8a:
			accumulator_add_8bitRegister( cpuRegisters.d, WITH_CARRY );
			break;
		case 0x8b:
			accumulator_add_8bitRegister( cpuRegisters.e, WITH_CARRY );
			break;
		case 0x8c:
			accumulator_add_8bitRegister( cpuRegisters.h, WITH_CARRY );
			break;
		case 0x8d:
			accumulator_add_8bitRegister( cpuRegisters.l, WITH_CARRY );
			break;
		case 0x8e:
			accumulator_add_memoryValue( WITH_CARRY );
			break;
		case 0x8f:
			accumulator_add_8bitRegister( cpuRegisters.a, WITH_CARRY );
			break;
		case 0x90:
			accumulator_sub_8bitRegister( cpuRegisters.b, NO_CARRY );
			break;
		case 0x91:
			accumulator_sub_8bitRegister( cpuRegisters.c, NO_CARRY );
			break;
		case 0x92:
			accumulator_sub_8bitRegister( cpuRegisters.d, NO_CARRY );
			break;
		case 0x93:
			accumulator_sub_8bitRegister( cpuRegisters.e, NO_CARRY );
			break;
		case 0x94:
			accumulator_sub_8bitRegister( cpuRegisters.h, NO_CARRY );
			break;
		case 0x95:
			accumulator_sub_8bitRegister( cpuRegisters.l, NO_CARRY );
			break;
		case 0x96:
			accumulator_sub_memoryValue( NO_CARRY );
			break;
		case 0x97:
			accumulator_sub_8bitRegister( cpuRegisters.a, NO_CARRY );
			break;
		case 0x98:
			accumulator_sub_8bitRegister( cpuRegisters.b, WITH_CARRY );
			break;
		case 0x99:
			accumulator_sub_8bitRegister( cpuRegisters.c, WITH_CARRY );
			break;
		case 0x9a:
			accumulator_sub_8bitRegister( cpuRegisters.d, WITH_CARRY );
			break;
		case 0x9b:
			accumulator_sub_8bitRegister( cpuRegisters.e, WITH_CARRY );
			break;
		case 0x9c:
			accumulator_sub_8bitRegister( cpuRegisters.h, WITH_CARRY );
			break;
		case 0x9d:
			accumulator_sub_8bitRegister( cpuRegisters.l, WITH_CARRY );
			break;
		case 0x9e:
			accumulator_sub_memoryValue( WITH_CARRY );
			break;
		case 0x9f:
			accumulator_sub_8bitRegister( cpuRegisters.a, WITH_CARRY );
			break;
		case 0xa0:
			accumulator_and_8bitRegister( cpuRegisters.b );
			break;
		case 0xa1:
			accumulator_and_8bitRegister( cpuRegisters.c );
			break;
		case 0xa2:
			accumulator_and_8bitRegister( cpuRegisters.d );
			break;
		case 0xa3:
			accumulator_and_8bitRegister( cpuRegisters.e );
			break;
		case 0xa4:
			accumulator_and_8bitRegister( cpuRegisters.h );
			break;
		case 0xa5:
			accumulator_and_8bitRegister( cpuRegisters.l );
			break;
		case 0xa6:
			accumulator_and_memoryValue();
			break;
		case 0xa7:
			accumulator_and_8bitRegister( cpuRegisters.a );
			break;
		case 0xa8:
			accumulator_xor_8bitRegister( cpuRegisters.b );
			break;
		case 0xa9:
			accumulator_xor_8bitRegister( cpuRegisters.c );
			break;
		case 0xaa:
			accumulator_xor_8bitRegister( cpuRegisters.d );
			break;
		case 0xab:
			accumulator_xor_8bitRegister( cpuRegisters.e );
			break;
		case 0xac:
			accumulator_xor_8bitRegister( cpuRegisters.h );
			break;
		case 0xad:
			accumulator_xor_8bitRegister( cpuRegisters.l );
			break;
		case 0xae:
			accumulator_xor_memoryValue();
			break;
		case 0xaf:
			accumulator_xor_8bitRegister( cpuRegisters.a );
			break;
		case 0xb0:
			accumulator_or_8bitRegister( cpuRegisters.b );
			break;
		case 0xb1:
			accumulator_or_8bitRegister( cpuRegisters.c );
			break;
		case 0xb2:
			accumulator_or_8bitRegister( cpuRegisters.d );
			break;
		case 0xb3:
			accumulator_or_8bitRegister( cpuRegisters.e );
			break;
		case 0xb4:
			accumulator_or_8bitRegister( cpuRegisters.h );
			break;
		case 0xb5:
			accumulator_or_8bitRegister( cpuRegisters.l );
			break;
		case 0xb6:
			accumulator_or_memoryValue();
			break;
		case 0xb7:
			accumulator_or_8bitRegister( cpuRegisters.a );
			break;
		case 0xb8:
			accumulator_cp_8bitRegister( cpuRegisters.b );
			break;
		case 0xb9:
			accumulator_cp_8bitRegister( cpuRegisters.c );
			break;
		case 0xba:
			accumulator_cp_8bitRegister( cpuRegisters.d );
			break;
		case 0xbb:
			accumulator_cp_8bitRegister( cpuRegisters.e );
			break;
		case 0xbc:
			accumulator_cp_8bitRegister( cpuRegisters.h );
			break;
		case 0xbd:
			accumulator_cp_8bitRegister( cpuRegisters.l );
			break;
		case 0xbe:
			accumulator_cp_memoryValue();
			break;
		case 0xbf:
			accumulator_cp_8bitRegister( cpuRegisters.a );
			break;
		case 0xc0:
			stack_return( CONDITION_NO_ZERO );
			break;
		case 0xc1:
			stack_pop( &cpuRegisters.bc );
			break;
		case 0xc2:
			jump_toAddressWord( CONDITION_NO_ZERO );
			break;
		case 0xc3:
			jump_toAddressWord( CONDITION_ALWAYS );
			break;
		case 0xc4:
			stack_call( CONDITION_NO_ZERO );
			break;
		case 0xc5:
			stack_push( cpuRegisters.bc );
			break;
		case 0xc6:
			accumulator_add_directByte( NO_CARRY );
			break;
		case 0xc7:
			stack_reset( 0x00 );
			break;
		case 0xc8:
			stack_return( CONDITION_ZERO );
			break;
		case 0xc9:
			stack_return( CONDITION_ALWAYS );
			break;
		case 0xca:
			jump_toAddressWord( CONDITION_ZERO );
			break;
		case 0xcb:
			cpu_prefix();
			break;
		case 0xcc:
			stack_call( CONDITION_ZERO );
			break;
		case 0xcd:
			stack_call( CONDITION_ALWAYS );
			break;
		case 0xce:
			accumulator_add_directByte( WITH_CARRY );
			break;
		case 0xcf:
			stack_reset( 0x08 );
			break;
		case 0xd0:
			stack_return( CONDITION_NO_CARRY );
			break;
		case 0xd1:
			stack_pop( &cpuRegisters.de );
			break;
		case 0xd2:
			jump_toAddressWord( CONDITION_NO_CARRY );
			break;
		case 0xd3:
			break;
		case 0xd4:
			stack_call( CONDITION_NO_CARRY );
			break;
		case 0xd5:
			stack_push( cpuRegisters.de );
			break;
		case 0xd6:
			accumulator_sub_directByte( NO_CARRY );
			break;
		case 0xd7:
			stack_reset( 0x10 );
			break;
		case 0xd8:
			stack_return( cpuRegisters.c );
			break;
		case 0xd9:
			stack_return( CONDITION_ALWAYS );
			cpu_enableInterrupts();
			break;
		case 0xda:
			jump_toAddressWord( CONDITION_CARRY );
			break;
		case 0xdb:
			break;
		case 0xdc:
			stack_call( cpuRegisters.c );
			break;
		case 0xdd:
			break;
		case 0xde:
			accumulator_sub_directByte( WITH_CARRY );
			break;
		case 0xdf:
			stack_reset( 0x18 );
			break;
		case 0xe0:
			load_memoryHighDirectOffset_A();
			break;
		case 0xe1:
			stack_pop( &cpuRegisters.hl );
			break;
		case 0xe2:
			load_memoryHighRegisterOffset_A(); //addr=ff00+c
			break;
		case 0xe3:
			break;
		case 0xe4:
			break;
		case 0xe5:
			stack_push( cpuRegisters.hl );
			break;
		case 0xe6:
			accumulator_and_directByte();
			break;
		case 0xe7:
			stack_reset( 0x20 );
			break;
		case 0xe8:
			stack_addDirectByteToSP();
			break;
		case 0xe9:
			jump_toHL();
			break;
		case 0xea:
			load_memoryAtDirectWord_A();
			break;
		case 0xeb:
			break;
		case 0xec:
			break;
		case 0xed:
			break;
		case 0xee:
			accumulator_xor_directByte();
			break;
		case 0xef:
			stack_reset( 0x28 );
			break;
		case 0xf0:
			load_A_MemoryHighWithDirectByteOffset();
			break;
		case 0xf1:
			stack_pop( &cpuRegisters.af );
			break;
		case 0xf2:
			load_A_MemoryHighWithRegisterByteOffset();
			break;
		case 0xf3:
			cpu_disableInterrupts();
			break;
		case 0xf4:
			break;
		case 0xf5:
			stack_push( cpuRegisters.af );
			break;
		case 0xf6:
			accumulator_or_directByte();
			break;
		case 0xf7:
			stack_reset( 0x30 );
			break;
		case 0xf8:
			stack_load_HL_SPWithDirectByteOffset();
			break;
		case 0xf9:
			stack_load_SP_HL();
			break;
		case 0xfa:
			load_A_MemoryAtDirectWord();
			break;
		case 0xfb:
			cpu_enableInterrupts();
			break;
		case 0xfc:
			break;
		case 0xfd:
			break;
		case 0xfe:
			accumulator_cp_directByte();
			break;
		case 0xff:
			stack_reset( 0x38 );
			break;
	}
}
