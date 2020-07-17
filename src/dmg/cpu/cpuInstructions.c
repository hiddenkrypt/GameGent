#include <stdio.h>
#include "registers.h"
#include "opcodes.h"
#include "../mmu/mmu.h"
#include "cpu.h"
#include "cpuInstructions.h"
#include "cpuInstructionHeaders.h"



/**
 * @todo prefix opcodes
 * @todo timing
 */



inline void executeInstruction( instruction opcode ){
	bool jump = instructionSwitch( MMU_readByte(cpuRegisters.pc) );
	if( !jump ){
        cpuRegisters.pc = cpuRegisters.pc + opcode.length;
	}
	handleStaticFlagEffects( opcode );
}
inline void handleStaticFlagEffects( instruction opcode ){
	if( opcode.flags.carry == EFFECT_RAISED ){
		CPU_setCarryFlag();
	}
	if( opcode.flags.carry == EFFECT_CLEARED ){
		CPU_clearCarryFlag();
	}
	if( opcode.flags.halfCarry == EFFECT_RAISED ){
		CPU_setHalfCarryFlag();
	}
	if( opcode.flags.halfCarry == EFFECT_CLEARED ){
		CPU_clearHalfCarryFlag();
	}
	if( opcode.flags.zero == EFFECT_RAISED ){
		CPU_setZeroFlag();
	}
	if( opcode.flags.zero == EFFECT_CLEARED ){
		CPU_clearZeroFlag();
	}
	if( opcode.flags.subtract == EFFECT_RAISED ){
		CPU_setSubtractFlag();
	}
	if( opcode.flags.carry == EFFECT_CLEARED ){
		CPU_clearSubtractFlag();
	}
	if( opcode.flags.zero == EFFECT_APPLIED && cpuRegisters.a == 0x00 ){
		CPU_setZeroFlag();
	}
}




inline bool instructionSwitch( uint8_t codePoint ){
	switch( codePoint ){
		case 0x00:
			CPU_noop();
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
			CPU_stop();
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
			return jump_relativeByte( CONDITION_ALWAYS );
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
			return jump_relativeByte( CONDITION_NO_ZERO );
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
			return jump_relativeByte( CONDITION_ZERO );
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
			return jump_relativeByte( CONDITION_NO_CARRY );
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
			CPU_setCarryFlag();
			break;
		case 0x38:
			return jump_relativeByte( CONDITION_CARRY );
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
			CPU_flipCarryFlag();
			break;
		case 0x40:
			CPU_noop();
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
			CPU_noop();
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
			CPU_noop();
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
			CPU_noop();
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
			CPU_noop();
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
			CPU_noop();
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
			CPU_halt();
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
			CPU_noop();
			break;
		case 0x80:
			accumulator_addition( cpuRegisters.b, NO_CARRY );
			break;
		case 0x81:
			accumulator_addition( cpuRegisters.c, NO_CARRY );
			break;
		case 0x82:
			accumulator_addition( cpuRegisters.d, NO_CARRY );
			break;
		case 0x83:
			accumulator_addition( cpuRegisters.e, NO_CARRY );
			break;
		case 0x84:
			accumulator_addition( cpuRegisters.h, NO_CARRY );
			break;
		case 0x85:
			accumulator_addition( cpuRegisters.l, NO_CARRY );
			break;
		case 0x86:
			accumulator_addition( MMU_readByte( cpuRegisters.hl ), NO_CARRY );
			break;
		case 0x87:
			accumulator_addition( cpuRegisters.a, NO_CARRY );
			break;
		case 0x88:
			accumulator_addition( cpuRegisters.b, WITH_CARRY );
			break;
		case 0x89:
			accumulator_addition( cpuRegisters.c, WITH_CARRY );
			break;
		case 0x8a:
			accumulator_addition( cpuRegisters.d, WITH_CARRY );
			break;
		case 0x8b:
			accumulator_addition( cpuRegisters.e, WITH_CARRY );
			break;
		case 0x8c:
			accumulator_addition( cpuRegisters.h, WITH_CARRY );
			break;
		case 0x8d:
			accumulator_addition( cpuRegisters.l, WITH_CARRY );
			break;
		case 0x8e:
			accumulator_addition( MMU_readByte( cpuRegisters.hl ), WITH_CARRY );
			break;
		case 0x8f:
			accumulator_addition( cpuRegisters.a, WITH_CARRY );
			break;
		case 0x90:
			accumulator_subtract( cpuRegisters.b, NO_CARRY );
			break;
		case 0x91:
			accumulator_subtract( cpuRegisters.c, NO_CARRY );
			break;
		case 0x92:
			accumulator_subtract( cpuRegisters.d, NO_CARRY );
			break;
		case 0x93:
			accumulator_subtract( cpuRegisters.e, NO_CARRY );
			break;
		case 0x94:
			accumulator_subtract( cpuRegisters.h, NO_CARRY );
			break;
		case 0x95:
			accumulator_subtract( cpuRegisters.l, NO_CARRY );
			break;
		case 0x96:
			accumulator_subtract( MMU_readByte( cpuRegisters.hl ), NO_CARRY );
			break;
		case 0x97:
			accumulator_subtract( cpuRegisters.a, NO_CARRY );
			break;
		case 0x98:
			accumulator_subtract( cpuRegisters.b, WITH_CARRY );
			break;
		case 0x99:
			accumulator_subtract( cpuRegisters.c, WITH_CARRY );
			break;
		case 0x9a:
			accumulator_subtract( cpuRegisters.d, WITH_CARRY );
			break;
		case 0x9b:
			accumulator_subtract( cpuRegisters.e, WITH_CARRY );
			break;
		case 0x9c:
			accumulator_subtract( cpuRegisters.h, WITH_CARRY );
			break;
		case 0x9d:
			accumulator_subtract( cpuRegisters.l, WITH_CARRY );
			break;
		case 0x9e:
			accumulator_subtract( MMU_readByte( cpuRegisters.hl ), WITH_CARRY );
			break;
		case 0x9f:
			accumulator_subtract( cpuRegisters.a, WITH_CARRY );
			break;
		case 0xa0:
			accumulator_logicalAnd( cpuRegisters.b );
			break;
		case 0xa1:
			accumulator_logicalAnd( cpuRegisters.c );
			break;
		case 0xa2:
			accumulator_logicalAnd( cpuRegisters.d );
			break;
		case 0xa3:
			accumulator_logicalAnd( cpuRegisters.e );
			break;
		case 0xa4:
			accumulator_logicalAnd( cpuRegisters.h );
			break;
		case 0xa5:
			accumulator_logicalAnd( cpuRegisters.l );
			break;
		case 0xa6:
			accumulator_logicalAnd( MMU_readByte( cpuRegisters.hl ) );
			break;
		case 0xa7:
			accumulator_logicalAnd( cpuRegisters.a );
			break;
		case 0xa8:
			accumulator_logicalXor( cpuRegisters.b );
			break;
		case 0xa9:
			accumulator_logicalXor( cpuRegisters.c );
			break;
		case 0xaa:
			accumulator_logicalXor( cpuRegisters.d );
			break;
		case 0xab:
			accumulator_logicalXor( cpuRegisters.e );
			break;
		case 0xac:
			accumulator_logicalXor( cpuRegisters.h );
			break;
		case 0xad:
			accumulator_logicalXor( cpuRegisters.l );
			break;
		case 0xae:
			accumulator_logicalXor( MMU_readByte( cpuRegisters.hl ) );
			break;
		case 0xaf:
			accumulator_logicalXor( cpuRegisters.a );
			break;
		case 0xb0:
			accumulator_logicalOr( cpuRegisters.b );
			break;
		case 0xb1:
			accumulator_logicalOr( cpuRegisters.c );
			break;
		case 0xb2:
			accumulator_logicalOr( cpuRegisters.d );
			break;
		case 0xb3:
			accumulator_logicalOr( cpuRegisters.e );
			break;
		case 0xb4:
			accumulator_logicalOr( cpuRegisters.h );
			break;
		case 0xb5:
			accumulator_logicalOr( cpuRegisters.l );
			break;
		case 0xb6:
			accumulator_logicalOr( MMU_readByte( cpuRegisters.hl ) );
			break;
		case 0xb7:
			accumulator_logicalOr( cpuRegisters.a );
			break;
		case 0xb8:
			accumulator_compare( cpuRegisters.b );
			break;
		case 0xb9:
			accumulator_compare( cpuRegisters.c );
			break;
		case 0xba:
			accumulator_compare( cpuRegisters.d );
			break;
		case 0xbb:
			accumulator_compare( cpuRegisters.e );
			break;
		case 0xbc:
			accumulator_compare( cpuRegisters.h );
			break;
		case 0xbd:
			accumulator_compare( cpuRegisters.l );
			break;
		case 0xbe:
			accumulator_compare( MMU_readByte( cpuRegisters.hl ) );
			break;
		case 0xbf:
			accumulator_compare( cpuRegisters.a );
			break;
		case 0xc0:
			stack_return( CONDITION_NO_ZERO );
			break;
		case 0xc1:
			stack_pop( &cpuRegisters.bc );
			break;
		case 0xc2:
			return jump_toAddressWord( CONDITION_NO_ZERO );
			break;
		case 0xc3:
			return jump_toAddressWord( CONDITION_ALWAYS );
			break;
		case 0xc4:
			stack_call( CONDITION_NO_ZERO );
			break;
		case 0xc5:
			stack_push( cpuRegisters.bc );
			break;
		case 0xc6:
			accumulator_addition( MMU_readByte( cpuRegisters.pc+1 ), NO_CARRY );
			break;
		case 0xc7:
			stack_restart( 0x00 );
			break;
		case 0xc8:
			stack_return( CONDITION_ZERO );
			break;
		case 0xc9:
			stack_return( CONDITION_ALWAYS );
			break;
		case 0xca:
			return jump_toAddressWord( CONDITION_ZERO );
			break;
		case 0xcb:
			prefixInstructionSwitch();
			break;
		case 0xcc:
			stack_call( CONDITION_ZERO );
			break;
		case 0xcd:
			stack_call( CONDITION_ALWAYS );
			break;
		case 0xce:
			accumulator_addition( MMU_readByte( cpuRegisters.pc+1 ), WITH_CARRY );
			break;
		case 0xcf:
			stack_restart( 0x08 );
			break;
		case 0xd0:
			stack_return( CONDITION_NO_CARRY );
			break;
		case 0xd1:
			stack_pop( &cpuRegisters.de );
			break;
		case 0xd2:
			return jump_toAddressWord( CONDITION_NO_CARRY );
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
			accumulator_subtract( MMU_readByte( cpuRegisters.pc+1 ), NO_CARRY );
			break;
		case 0xd7:
			stack_restart( 0x10 );
			break;
		case 0xd8:
			stack_return( cpuRegisters.c );
			break;
		case 0xd9:
			stack_return( CONDITION_ALWAYS );
			CPU_enableInterrupts();
			break;
		case 0xda:
			return jump_toAddressWord( CONDITION_CARRY );
			break;
		case 0xdb:
			break;
		case 0xdc:
			stack_call( cpuRegisters.c );
			break;
		case 0xdd:
			break;
		case 0xde:
			accumulator_subtract( MMU_readByte( cpuRegisters.pc+1 ), WITH_CARRY );
			break;
		case 0xdf:
			stack_restart( 0x18 );
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
			accumulator_logicalAnd( MMU_readByte( cpuRegisters.pc+1 ) );
			break;
		case 0xe7:
			stack_restart( 0x20 );
			break;
		case 0xe8:
			stack_addDirectByteToSP();
			break;
		case 0xe9:
			return jump_toHL();
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
			accumulator_logicalXor( MMU_readByte( cpuRegisters.pc+1 ) );
			break;
		case 0xef:
			stack_restart( 0x28 );
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
			CPU_disableInterrupts();
			break;
		case 0xf4:
			break;
		case 0xf5:
			stack_push( cpuRegisters.af );
			break;
		case 0xf6:
			accumulator_logicalOr( MMU_readByte( cpuRegisters.pc+1 ) );
			break;
		case 0xf7:
			stack_restart( 0x30 );
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
			CPU_enableInterrupts();
			break;
		case 0xfc:
			break;
		case 0xfd:
			break;
		case 0xfe:
			accumulator_compare( MMU_readByte( cpuRegisters.pc+1 ) );
			break;
		case 0xff:
			stack_restart( 0x38 );
			break;
	}
	return false;
}

inline void prefixInstructionSwitch(){
	switch ( MMU_readByte( cpuRegisters.pc+1 ) ){
		case 0x00:
			rotate_8bitRegister( &cpuRegisters.b, LEFT, NO_CARRY );
			break;
		case 0x01:
			rotate_8bitRegister( &cpuRegisters.c, LEFT, NO_CARRY );
			break;
		case 0x02:
			rotate_8bitRegister( &cpuRegisters.d, LEFT, NO_CARRY );
			break;
		case 0x03:
			rotate_8bitRegister( &cpuRegisters.e, LEFT, NO_CARRY );
			break;
		case 0x04:
			rotate_8bitRegister( &cpuRegisters.h, LEFT, NO_CARRY );
			break;
		case 0x05:
			rotate_8bitRegister( &cpuRegisters.l, LEFT, NO_CARRY );
			break;
		case 0x06:
			rotate_memoryByte( RIGHT, NO_CARRY );
			break;
		case 0x07:
			rotate_8bitRegister( &cpuRegisters.a, LEFT, NO_CARRY );
			break;
		case 0x08:
			rotate_8bitRegister( &cpuRegisters.b, RIGHT, NO_CARRY );
			break;
		case 0x09:
			rotate_8bitRegister( &cpuRegisters.c, RIGHT, NO_CARRY );
			break;
		case 0x0a:
			rotate_8bitRegister( &cpuRegisters.d, RIGHT, NO_CARRY );
			break;
		case 0x0b:
			rotate_8bitRegister( &cpuRegisters.e, RIGHT, NO_CARRY );
			break;
		case 0x0c:
			rotate_8bitRegister( &cpuRegisters.h, RIGHT, NO_CARRY );
			break;
		case 0x0d:
			rotate_8bitRegister( &cpuRegisters.l, RIGHT, NO_CARRY );
			break;
		case 0x0e:
			rotate_memoryByte( RIGHT, NO_CARRY );
			break;
		case 0x0f:
			rotate_8bitRegister( &cpuRegisters.a, RIGHT, NO_CARRY );
			break;
		case 0x10:
			rotate_8bitRegister( &cpuRegisters.b, LEFT, THROUGH_CARRY );
			break;
		case 0x11:
			rotate_8bitRegister( &cpuRegisters.c, LEFT, THROUGH_CARRY );
			break;
		case 0x12:
			rotate_8bitRegister( &cpuRegisters.d, LEFT, THROUGH_CARRY );
			break;
		case 0x13:
			rotate_8bitRegister( &cpuRegisters.e, LEFT, THROUGH_CARRY );
			break;
		case 0x14:
			rotate_8bitRegister( &cpuRegisters.h, LEFT, THROUGH_CARRY );
			break;
		case 0x15:
			rotate_8bitRegister( &cpuRegisters.l, LEFT, THROUGH_CARRY );
			break;
		case 0x16:
			rotate_memoryByte( LEFT, THROUGH_CARRY );
			break;
		case 0x17:
			rotate_8bitRegister( &cpuRegisters.a, LEFT, THROUGH_CARRY );
			break;
		case 0x18:
			rotate_8bitRegister( &cpuRegisters.b, RIGHT, THROUGH_CARRY );
			break;
		case 0x19:
			rotate_8bitRegister( &cpuRegisters.b, RIGHT, THROUGH_CARRY );
			break;
		case 0x1a:
			rotate_8bitRegister( &cpuRegisters.b, RIGHT, THROUGH_CARRY );
			break;
		case 0x1b:
			rotate_8bitRegister( &cpuRegisters.b, RIGHT, THROUGH_CARRY );
			break;
		case 0x1c:
			rotate_8bitRegister( &cpuRegisters.b, RIGHT, THROUGH_CARRY );
			break;
		case 0x1d:
			rotate_8bitRegister( &cpuRegisters.b, RIGHT, THROUGH_CARRY );
			break;
		case 0x1e:
			rotate_memoryByte( RIGHT, THROUGH_CARRY );
			break;
		case 0x1f:
			rotate_8bitRegister( &cpuRegisters.a, RIGHT, THROUGH_CARRY );
			break;
		case 0x20:
		    shift( &cpuRegisters.b, LEFT, RESET_SIGNIFICANT_BIT );
			break;
		case 0x21:
		    shift( &cpuRegisters.c, LEFT, RESET_SIGNIFICANT_BIT );
			break;
		case 0x22:
		    shift( &cpuRegisters.d, LEFT, RESET_SIGNIFICANT_BIT );
			break;
		case 0x23:
		    shift( &cpuRegisters.e, LEFT, RESET_SIGNIFICANT_BIT );
			break;
		case 0x24:
		    shift( &cpuRegisters.h, LEFT, RESET_SIGNIFICANT_BIT );
			break;
		case 0x25:
		    shift( &cpuRegisters.l, LEFT, RESET_SIGNIFICANT_BIT );
			break;
		case 0x26:
		    shift_memory( LEFT, RESET_SIGNIFICANT_BIT );
			break;
		case 0x27:
		    shift( &cpuRegisters.a, LEFT, RESET_SIGNIFICANT_BIT );
			break;
		case 0x28:
		    shift( &cpuRegisters.b, RIGHT, NO_RESET_SIGNIFICANT_BIT );
			break;
		case 0x29:
		    shift( &cpuRegisters.c, RIGHT, NO_RESET_SIGNIFICANT_BIT );
			break;
		case 0x2a:
		    shift( &cpuRegisters.d, RIGHT, NO_RESET_SIGNIFICANT_BIT );
			break;
		case 0x2b:
		    shift( &cpuRegisters.e, RIGHT, NO_RESET_SIGNIFICANT_BIT );
			break;
		case 0x2c:
		    shift( &cpuRegisters.h, RIGHT, NO_RESET_SIGNIFICANT_BIT );
			break;
		case 0x2d:
		    shift( &cpuRegisters.l, RIGHT, NO_RESET_SIGNIFICANT_BIT );
			break;
		case 0x2e:
		    shift_memory( RIGHT, NO_RESET_SIGNIFICANT_BIT );
			break;
		case 0x2f:
		    shift( &cpuRegisters.a, RIGHT, NO_RESET_SIGNIFICANT_BIT );
			break;
		case 0x30:
            swapNibbles( &cpuRegisters.b );
			break;
		case 0x31:
            swapNibbles( &cpuRegisters.c );
			break;
		case 0x32:
            swapNibbles( &cpuRegisters.d );
			break;
		case 0x33:
            swapNibbles( &cpuRegisters.e );
			break;
		case 0x34:
            swapNibbles( &cpuRegisters.h );
			break;
		case 0x35:
            swapNibbles( &cpuRegisters.l );
			break;
		case 0x36:
            swapMemoryNibbles();
			break;
		case 0x37:
		    swapNibbles( &cpuRegisters.a );
			break;
		case 0x38:
		    shift( &cpuRegisters.b, RIGHT, RESET_SIGNIFICANT_BIT );
			break;
		case 0x39:
		    shift( &cpuRegisters.c, RIGHT, RESET_SIGNIFICANT_BIT );
			break;
		case 0x3a:
		    shift( &cpuRegisters.d, RIGHT, RESET_SIGNIFICANT_BIT );
			break;
		case 0x3b:
		    shift( &cpuRegisters.e, RIGHT, RESET_SIGNIFICANT_BIT );
			break;
		case 0x3c:
		    shift( &cpuRegisters.h, RIGHT, RESET_SIGNIFICANT_BIT );
			break;
		case 0x3d:
		    shift( &cpuRegisters.l, RIGHT, RESET_SIGNIFICANT_BIT );
			break;
		case 0x3e:
		    shift_memory( RIGHT, RESET_SIGNIFICANT_BIT );
			break;
		case 0x3f:
		    shift( &cpuRegisters.a, RIGHT, RESET_SIGNIFICANT_BIT );
			break;
		case 0x40:
			bit_read( BIT_ZERO, &cpuRegisters.b );
			break;
		case 0x41:
			bit_read( BIT_ZERO, &cpuRegisters.c );
			break;
		case 0x42:
			bit_read( BIT_ZERO, &cpuRegisters.d );
			break;
		case 0x43:
			bit_read( BIT_ZERO, &cpuRegisters.e );
			break;
		case 0x44:
			bit_read( BIT_ZERO, &cpuRegisters.h );
			break;
		case 0x45:
			bit_read( BIT_ZERO, &cpuRegisters.l );
			break;
		case 0x46:
			bit_memoryRead( BIT_ZERO );
			break;
		case 0x47:
			bit_read( BIT_ZERO, &cpuRegisters.a );
			break;
		case 0x48:
			bit_read( BIT_ONE, &cpuRegisters.b );
			break;
		case 0x49:
			bit_read( BIT_ONE, &cpuRegisters.c );
			break;
		case 0x4a:
			bit_read( BIT_ONE, &cpuRegisters.d );
			break;
		case 0x4b:
			bit_read( BIT_ONE, &cpuRegisters.e );
			break;
		case 0x4c:
			bit_read( BIT_ONE, &cpuRegisters.h );
			break;
		case 0x4d:
			bit_read( BIT_ONE, &cpuRegisters.l );
			break;
		case 0x4e:
			bit_memoryRead( BIT_ONE );
			break;
		case 0x4f:
			bit_read( BIT_ONE, &cpuRegisters.a );
			break;
		case 0x50:
			bit_read( BIT_TWO, &cpuRegisters.b );
			break;
		case 0x51:
			bit_read( BIT_TWO, &cpuRegisters.c );
			break;
		case 0x52:
			bit_read( BIT_TWO, &cpuRegisters.d );
			break;
		case 0x53:
			bit_read( BIT_TWO, &cpuRegisters.e );
			break;
		case 0x54:
			bit_read( BIT_TWO, &cpuRegisters.h );
			break;
		case 0x55:
			bit_read( BIT_TWO, &cpuRegisters.l );
			break;
		case 0x56:
			bit_memoryRead( BIT_TWO );
			break;
		case 0x57:
			bit_read( BIT_TWO, &cpuRegisters.a );
			break;
		case 0x58:
			bit_read( BIT_THREE, &cpuRegisters.b );
			break;
		case 0x59:
			bit_read( BIT_THREE, &cpuRegisters.c );
			break;
		case 0x5a:
			bit_read( BIT_THREE, &cpuRegisters.d );
			break;
		case 0x5b:
			bit_read( BIT_THREE, &cpuRegisters.e );
			break;
		case 0x5c:
			bit_read( BIT_THREE, &cpuRegisters.h );
			break;
		case 0x5d:
			bit_read( BIT_THREE, &cpuRegisters.l );
			break;
		case 0x5e:
			bit_memoryRead( BIT_THREE );
			break;
		case 0x5f:
			bit_read( BIT_THREE, &cpuRegisters.a );
			break;
		case 0x60:
			bit_read( BIT_FOUR, &cpuRegisters.b );
			break;
		case 0x61:
			bit_read( BIT_FOUR, &cpuRegisters.c );
			break;
		case 0x62:
			bit_read( BIT_FOUR, &cpuRegisters.d );
			break;
		case 0x63:
			bit_read( BIT_FOUR, &cpuRegisters.e );
			break;
		case 0x64:
			bit_read( BIT_FOUR, &cpuRegisters.h );
			break;
		case 0x65:
			bit_read( BIT_FOUR, &cpuRegisters.l );
			break;
		case 0x66:
			bit_memoryRead( BIT_FOUR);
			break;
		case 0x67:
			bit_read( BIT_FOUR, &cpuRegisters.a );
			break;
		case 0x68:
			bit_read( BIT_FIVE, &cpuRegisters.b );
			break;
		case 0x69:
			bit_read( BIT_FIVE, &cpuRegisters.c );
			break;
		case 0x6a:
			bit_read( BIT_FIVE, &cpuRegisters.d );
			break;
		case 0x6b:
			bit_read( BIT_FIVE, &cpuRegisters.e );
			break;
		case 0x6c:
			bit_read( BIT_FIVE, &cpuRegisters.h );
			break;
		case 0x6d:
			bit_read( BIT_FIVE, &cpuRegisters.l );
			break;
		case 0x6e:
			bit_memoryRead( BIT_FIVE );
			break;
		case 0x6f:
			bit_read( BIT_FIVE, &cpuRegisters.a );
			break;
		case 0x70:
			bit_read( BIT_SIX, &cpuRegisters.b );
			break;
		case 0x71:
			bit_read( BIT_SIX, &cpuRegisters.c );
			break;
		case 0x72:
			bit_read( BIT_SIX, &cpuRegisters.d );
			break;
		case 0x73:
			bit_read( BIT_SIX, &cpuRegisters.e );
			break;
		case 0x74:
			bit_read( BIT_SIX, &cpuRegisters.h );
			break;
		case 0x75:
			bit_read( BIT_SIX, &cpuRegisters.l );
			break;
		case 0x76:
			bit_memoryRead( BIT_SIX );
			break;
		case 0x77:
			bit_read( BIT_SIX, &cpuRegisters.a );
			break;
		case 0x78:
			bit_read( BIT_SEVEN, &cpuRegisters.b );
			break;
		case 0x79:
			bit_read( BIT_SEVEN, &cpuRegisters.c );
			break;
		case 0x7a:
			bit_read( BIT_SEVEN, &cpuRegisters.d );
			break;
		case 0x7b:
			bit_read( BIT_SEVEN, &cpuRegisters.e );
			break;
		case 0x7c:
			bit_read( BIT_SEVEN, &cpuRegisters.h );
			break;
		case 0x7d:
			bit_read( BIT_SEVEN, &cpuRegisters.l );
			break;
		case 0x7e:
			bit_memoryRead( BIT_SEVEN );
			break;
		case 0x7f:
			bit_read( BIT_SEVEN, &cpuRegisters.a );
			break;
		case 0x80:
			bit_reset( BIT_ZERO, &cpuRegisters.b );
			break;
		case 0x81:
			bit_reset( BIT_ZERO, &cpuRegisters.c );
			break;
		case 0x82:
			bit_reset( BIT_ZERO, &cpuRegisters.d );
			break;
		case 0x83:
			bit_reset( BIT_ZERO, &cpuRegisters.e );
			break;
		case 0x84:
			bit_reset( BIT_ZERO, &cpuRegisters.h );
			break;
		case 0x85:
			bit_reset( BIT_ZERO, &cpuRegisters.l );
			break;
		case 0x86:
			bit_memoryReset( BIT_ZERO );
			break;
		case 0x87:
			bit_reset( BIT_ZERO, &cpuRegisters.a );
			break;
		case 0x88:
			bit_reset( BIT_ONE, &cpuRegisters.b );
			break;
		case 0x89:
			bit_reset( BIT_ONE, &cpuRegisters.c );
			break;
		case 0x8a:
			bit_reset( BIT_ONE, &cpuRegisters.d );
			break;
		case 0x8b:
			bit_reset( BIT_ONE, &cpuRegisters.e );
			break;
		case 0x8c:
			bit_reset( BIT_ONE, &cpuRegisters.h );
			break;
		case 0x8d:
			bit_reset( BIT_ONE, &cpuRegisters.l );
			break;
		case 0x8e:
			bit_memoryReset( BIT_ONE );
			break;
		case 0x8f:
			bit_reset( BIT_ONE, &cpuRegisters.a );
			break;
		case 0x90:
			bit_reset( BIT_TWO, &cpuRegisters.b );
			break;
		case 0x91:
			bit_reset( BIT_TWO, &cpuRegisters.c );
			break;
		case 0x92:
			bit_reset( BIT_TWO, &cpuRegisters.d );
			break;
		case 0x93:
			bit_reset( BIT_TWO, &cpuRegisters.e );
			break;
		case 0x94:
			bit_reset( BIT_TWO, &cpuRegisters.h );
			break;
		case 0x95:
			bit_reset( BIT_TWO, &cpuRegisters.l );
			break;
		case 0x96:
			bit_memoryReset( BIT_TWO );
			break;
		case 0x97:
			bit_reset( BIT_TWO, &cpuRegisters.a );
			break;
		case 0x98:
			bit_reset( BIT_THREE, &cpuRegisters.b );
			break;
		case 0x99:
			bit_reset( BIT_THREE, &cpuRegisters.c );
			break;
		case 0x9a:
			bit_reset( BIT_THREE, &cpuRegisters.d );
			break;
		case 0x9b:
			bit_reset( BIT_THREE, &cpuRegisters.e );
			break;
		case 0x9c:
			bit_reset( BIT_THREE, &cpuRegisters.h );
			break;
		case 0x9d:
			bit_reset( BIT_THREE, &cpuRegisters.l );
			break;
		case 0x9e:
			bit_memoryReset( BIT_THREE );
			break;
		case 0x9f:
			bit_reset( BIT_THREE, &cpuRegisters.a );
			break;
		case 0xa0:
			bit_reset( BIT_FOUR, &cpuRegisters.b );
			break;
		case 0xa1:
			bit_reset( BIT_FOUR, &cpuRegisters.c );
			break;
		case 0xa2:
			bit_reset( BIT_FOUR, &cpuRegisters.d );
			break;
		case 0xa3:
			bit_reset( BIT_FOUR, &cpuRegisters.e );
			break;
		case 0xa4:
			bit_reset( BIT_FOUR, &cpuRegisters.h );
			break;
		case 0xa5:
			bit_reset( BIT_FOUR, &cpuRegisters.l );
			break;
		case 0xa6:
			bit_memoryReset( BIT_FOUR );
			break;
		case 0xa7:
			bit_reset( BIT_FOUR, &cpuRegisters.a );
			break;
		case 0xa8:
			bit_reset( BIT_FIVE, &cpuRegisters.b );
			break;
		case 0xa9:
			bit_reset( BIT_FIVE, &cpuRegisters.c );
			break;
		case 0xaa:
			bit_reset( BIT_FIVE, &cpuRegisters.d );
			break;
		case 0xab:
			bit_reset( BIT_FIVE, &cpuRegisters.e );
			break;
		case 0xac:
			bit_reset( BIT_FIVE, &cpuRegisters.h );
			break;
		case 0xad:
			bit_reset( BIT_FIVE, &cpuRegisters.l );
			break;
		case 0xae:
			bit_memoryReset( BIT_FIVE );
			break;
		case 0xaf:
			bit_reset( BIT_FIVE, &cpuRegisters.a );
			break;
		case 0xb0:
			bit_reset( BIT_SIX, &cpuRegisters.b );
			break;
		case 0xb1:
			bit_reset( BIT_SIX, &cpuRegisters.c );
			break;
		case 0xb2:
			bit_reset( BIT_SIX, &cpuRegisters.d );
			break;
		case 0xb3:
			bit_reset( BIT_SIX, &cpuRegisters.e );
			break;
		case 0xb4:
			bit_reset( BIT_SIX, &cpuRegisters.h );
			break;
		case 0xb5:
			bit_reset( BIT_SIX, &cpuRegisters.l );
			break;
		case 0xb6:
			bit_memoryReset( BIT_SIX );
			break;
		case 0xb7:
			bit_reset( BIT_SIX, &cpuRegisters.a );
			break;
		case 0xb8:
			bit_reset( BIT_SEVEN, &cpuRegisters.b );
			break;
		case 0xb9:
			bit_reset( BIT_SEVEN, &cpuRegisters.c );
			break;
		case 0xba:
			bit_reset( BIT_SEVEN, &cpuRegisters.d );
			break;
		case 0xbb:
			bit_reset( BIT_SEVEN, &cpuRegisters.e );
			break;
		case 0xbc:
			bit_reset( BIT_SEVEN, &cpuRegisters.h );
			break;
		case 0xbd:
			bit_reset( BIT_SEVEN, &cpuRegisters.l );
			break;
		case 0xbe:
			bit_memoryReset( BIT_SEVEN );
			break;
		case 0xbf:
			bit_reset( BIT_SEVEN, &cpuRegisters.a );
			break;
		case 0xc0:
			bit_set( BIT_ZERO, &cpuRegisters.b );
			break;
		case 0xc1:
			bit_set( BIT_ZERO, &cpuRegisters.c );
			break;
		case 0xc2:
			bit_set( BIT_ZERO, &cpuRegisters.d );
			break;
		case 0xc3:
			bit_set( BIT_ZERO, &cpuRegisters.e );
			break;
		case 0xc4:
			bit_set( BIT_ZERO, &cpuRegisters.h );
			break;
		case 0xc5:
			bit_set( BIT_ZERO, &cpuRegisters.l );
			break;
		case 0xc6:
			bit_memorySet( BIT_ZERO );
			break;
		case 0xc7:
			bit_set( BIT_ZERO, &cpuRegisters.a );
			break;
		case 0xc8:
			bit_set( BIT_ONE, &cpuRegisters.b );
			break;
		case 0xc9:
			bit_set( BIT_ONE, &cpuRegisters.c );
			break;
		case 0xca:
			bit_set( BIT_ONE, &cpuRegisters.d );
			break;
		case 0xcb:
			bit_set( BIT_ONE, &cpuRegisters.e );
			break;
		case 0xcc:
			bit_set( BIT_ONE, &cpuRegisters.h );
			break;
		case 0xcd:
			bit_set( BIT_ONE, &cpuRegisters.l );
			break;
		case 0xce:
			bit_memorySet( BIT_ONE );
			break;
		case 0xcf:
			bit_set( BIT_ONE, &cpuRegisters.a );
			break;
		case 0xd0:
			bit_set( BIT_TWO, &cpuRegisters.b );
			break;
		case 0xd1:
			bit_set( BIT_TWO, &cpuRegisters.c );
			break;
		case 0xd2:
			bit_set( BIT_TWO, &cpuRegisters.d );
			break;
		case 0xd3:
			bit_set( BIT_TWO, &cpuRegisters.e );
			break;
		case 0xd4:
			bit_set( BIT_TWO, &cpuRegisters.h );
			break;
		case 0xd5:
			bit_set( BIT_TWO, &cpuRegisters.l );
			break;
		case 0xd6:
			bit_memorySet( BIT_TWO );
			break;
		case 0xd7:
			bit_set( BIT_TWO, &cpuRegisters.a );
			break;
		case 0xd8:
			bit_set( BIT_THREE, &cpuRegisters.b );
			break;
		case 0xd9:
			bit_set( BIT_THREE, &cpuRegisters.c );
			break;
		case 0xda:
			bit_set( BIT_THREE, &cpuRegisters.d );
			break;
		case 0xdb:
			bit_set( BIT_THREE, &cpuRegisters.e );
			break;
		case 0xdc:
			bit_set( BIT_THREE, &cpuRegisters.h );
			break;
		case 0xdd:
			bit_set( BIT_THREE, &cpuRegisters.l );
			break;
		case 0xde:
			bit_memorySet( BIT_THREE );
			break;
		case 0xdf:
			bit_set( BIT_THREE, &cpuRegisters.a );
			break;
		case 0xe0:
			bit_set( BIT_FOUR, &cpuRegisters.b );
			break;
		case 0xe1:
			bit_set( BIT_FOUR, &cpuRegisters.c );
			break;
		case 0xe2:
			bit_set( BIT_FOUR, &cpuRegisters.d );
			break;
		case 0xe3:
			bit_set( BIT_FOUR, &cpuRegisters.e );
			break;
		case 0xe4:
			bit_set( BIT_FOUR, &cpuRegisters.h );
			break;
		case 0xe5:
			bit_set( BIT_FOUR, &cpuRegisters.l );
			break;
		case 0xe6:
			bit_memorySet( BIT_FOUR );
			break;
		case 0xe7:
			bit_set( BIT_FOUR, &cpuRegisters.a );
			break;
		case 0xe8:
			bit_set( BIT_FIVE, &cpuRegisters.b );
			break;
		case 0xe9:
			bit_set( BIT_FIVE, &cpuRegisters.c );
			break;
		case 0xea:
			bit_set( BIT_FIVE, &cpuRegisters.d );
			break;
		case 0xeb:
			bit_set( BIT_FIVE, &cpuRegisters.e );
			break;
		case 0xec:
			bit_set( BIT_FIVE, &cpuRegisters.h );
			break;
		case 0xed:
			bit_set( BIT_FIVE, &cpuRegisters.l );
			break;
		case 0xee:
			bit_memorySet( BIT_FIVE );
			break;
		case 0xef:
			bit_set( BIT_FIVE, &cpuRegisters.a );
			break;
		case 0xf0:
			bit_set( BIT_SIX, &cpuRegisters.b );
			break;
		case 0xf1:
			bit_set( BIT_SIX, &cpuRegisters.c );
			break;
		case 0xf2:
			bit_set( BIT_SIX, &cpuRegisters.d );
			break;
		case 0xf3:
			bit_set( BIT_SIX, &cpuRegisters.e );
			break;
		case 0xf4:
			bit_set( BIT_SIX, &cpuRegisters.h );
			break;
		case 0xf5:
			bit_set( BIT_SIX, &cpuRegisters.l );
			break;
		case 0xf6:
			bit_memorySet( BIT_SIX );
			break;
		case 0xf7:
			bit_set( BIT_SIX, &cpuRegisters.a );
			break;
		case 0xf8:
			bit_set( BIT_SEVEN, &cpuRegisters.b );
			break;
		case 0xf9:
			bit_set( BIT_SEVEN, &cpuRegisters.c );
			break;
		case 0xfa:
			bit_set( BIT_SEVEN, &cpuRegisters.d );
			break;
		case 0xfb:
			bit_set( BIT_SEVEN, &cpuRegisters.e );
			break;
		case 0xfc:
			bit_set( BIT_SEVEN, &cpuRegisters.l );
			break;
		case 0xfd:
			bit_set( BIT_SEVEN, &cpuRegisters.h );
			break;
		case 0xfe:
			bit_memorySet( BIT_SEVEN );
			break;
		case 0xff:
			bit_set( BIT_SEVEN, &cpuRegisters.a );
			break;
	}
}

inline void load_16bitRegister_DirectWord( uint16_t* targetRegister ){
	*targetRegister = MMU_readWord( cpuRegisters.pc + 1 );
}
inline void load_8bitRegister_DirectByte( uint8_t* targetRegister ){
	*targetRegister = MMU_readWord( cpuRegisters.pc + 1 );
}
inline void load_8bitRegister_MemoryAtRegisterValue( uint8_t* targetRegister, uint16_t address ){
	*targetRegister = MMU_readWord( address );
}
inline void load_8bitRegister_8bitRegister( uint8_t* targetRegister, uint8_t dataRegister ){
	*targetRegister = dataRegister;
}
inline void load_memory_directByte(){
	MMU_loadByte( cpuRegisters.hl, MMU_readByte( cpuRegisters.pc + 1 ) );
}
inline void load_memoryAtRegisterValue_8bitRegisterData( uint16_t address, uint8_t dataRegister ){
	MMU_loadByte( address, dataRegister );
}
inline void load_memoryAtDirectWord_16bitRegister(){
	MMU_loadWord( MMU_readWord( cpuRegisters.pc + 1 ), cpuRegisters.sp );
}
inline void load_memoryAtDirectWord_A(){
	MMU_loadByte( MMU_readWord( cpuRegisters.pc + 1 ), cpuRegisters.a );
}
inline void load_memoryHighDirectOffset_A(){
	MMU_loadByte( 0xff00 + MMU_readByte( cpuRegisters.pc + 1 ), cpuRegisters.a );
}
inline void load_memoryHighRegisterOffset_A(){
	MMU_loadByte( 0xff00 + cpuRegisters.c, cpuRegisters.a );
}
inline void load_A_MemoryAtDirectWord(){
	cpuRegisters.a = MMU_readByte( cpuRegisters.pc + 1 );
}
inline void load_A_MemoryHighWithDirectByteOffset(){
	cpuRegisters.a = MMU_readByte( 0xff00 + MMU_readByte( cpuRegisters.pc + 1 ) );
}
inline void load_A_MemoryHighWithRegisterByteOffset(){
	cpuRegisters.a = MMU_readByte( 0xff00 + cpuRegisters.c );
}

inline void increment_16bitRegister( uint16_t* targetRegister ){
	*targetRegister = *targetRegister+1;
}
inline void decrement_16bitRegister( uint16_t* targetRegister ){
	*targetRegister = *targetRegister-1;
}
inline void increment_8bitRegister( uint8_t* targetRegister ){
	if( !( *targetRegister & 0x0F ) ) {
		CPU_setHalfCarryFlag();
	}
	*targetRegister = *targetRegister + 1;
	if( *targetRegister == 0 ){
		CPU_setZeroFlag();
	}
	if( !( *targetRegister & 0x0F ) ) {
		CPU_setHalfCarryFlag();
	}
}
inline void decrement_8bitRegister( uint8_t* targetRegister ){
	*targetRegister = *targetRegister-1;
	if( ( *targetRegister & 0x0f ) == 0x0f ){
		CPU_setHalfCarryFlag();
	}
	if( *targetRegister == 0 ){
		CPU_setZeroFlag();
	}
}
inline void increment_memoryValue(){
	MMU_loadByte( cpuRegisters.hl, MMU_readByte( cpuRegisters.hl ) + 1 );
	if( MMU_readByte( cpuRegisters.hl ) == 0 ){
		CPU_setZeroFlag();
	}
	if( !( MMU_readByte( cpuRegisters.hl ) & 0x0F ) ) {
		CPU_setHalfCarryFlag();
	}
}
inline void decrement_memoryValue(){
	MMU_loadByte( cpuRegisters.hl, MMU_readByte( cpuRegisters.hl ) - 1 );
	if( MMU_readByte( cpuRegisters.hl ) == 0 ){
		CPU_setZeroFlag();
	}
	if( ( MMU_readByte( cpuRegisters.hl ) & 0x0f ) == 0x0f ){
		CPU_setHalfCarryFlag();
	}
}

inline void rotate_memoryByte( direction leftOrRight, carryPolicy throughCarry ){
	uint8_t memoryValue = MMU_readByte( cpuRegisters.hl );
	rotate_8bitRegister( &memoryValue, leftOrRight, throughCarry );
	MMU_loadByte( cpuRegisters.hl, memoryValue );
}

inline void rotate_8bitRegister( uint8_t* targetRegister, direction leftOrRight, carryPolicy throughCarry ){
	if( leftOrRight == LEFT ){
		uint8_t msb = *targetRegister >> 7;
		*targetRegister = *targetRegister << 1;
		if( throughCarry ){
			uint8_t previousCarry = CPU_getCarryFlag();
			if( msb ){
				CPU_setCarryFlag();
			} else {
				CPU_clearCarryFlag();
			}
			if( previousCarry ){
				*targetRegister = *targetRegister | 0x01;
			} else {
				*targetRegister = *targetRegister & 0xfe;
			}
		} else {
			if( msb ){
				CPU_setCarryFlag();
				*targetRegister = *targetRegister | 0x01;
			} else {
				CPU_clearCarryFlag();
				*targetRegister = *targetRegister & 0xfe;
			}
		}
	} else {
		uint8_t lsb = *targetRegister & 0x01;
		*targetRegister = *targetRegister >> 1;
		if( throughCarry ){
			uint8_t previousCarry = CPU_getCarryFlag();
			if( lsb ){
				CPU_setCarryFlag();
			} else {
				CPU_clearCarryFlag();
			}
			if( previousCarry ){
				*targetRegister = *targetRegister | 0x80;
			} else {
				*targetRegister = *targetRegister & 0x7f;
			}
		} else {
			if( lsb ){
				CPU_setCarryFlag();
				*targetRegister = *targetRegister | 0x80;
			} else {
				CPU_clearCarryFlag();
				*targetRegister = *targetRegister & 0x7f;
			}
		}
	}
	if( *targetRegister == 0 ){
		CPU_setZeroFlag();
	}
}

inline void add_16bitRegister( uint16_t valueRegister ){
	if( ( ( cpuRegisters.hl & 0x0fff ) + ( valueRegister & 0x0fff ) ) &0x1000 ){
		CPU_setHalfCarryFlag();
	}
	cpuRegisters.hl = cpuRegisters.hl + valueRegister;
	if( cpuRegisters.hl < valueRegister ){
		CPU_setCarryFlag();
	}
}


inline void accumulator_decimalAdjustment(){
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
		CPU_setCarryFlag();
	}
	cpuRegisters.a = workingValue & 0xff;
}
inline void accumulator_complement(){
	cpuRegisters.a = ~cpuRegisters.a;
}
inline void accumulator_addition( uint8_t value, carryPolicy carryUse ){
	cpuRegisters.a = cpuRegisters.a + value;
	if( carryUse ){
		cpuRegisters.a = cpuRegisters.a + CPU_getCarryFlag();
	}
	if( cpuRegisters.a < value ){
		CPU_setCarryFlag();
	}
}
inline void accumulator_subtract( uint8_t value, carryPolicy carryUse ){
	uint8_t valueA = cpuRegisters.a;
	cpuRegisters.a = cpuRegisters.a - value;
	if( carryUse ){
		cpuRegisters.a = cpuRegisters.a - CPU_getCarryFlag();
	}
	if( cpuRegisters.a == 0 ){
		CPU_setZeroFlag();
	}
	if( ( valueA & 0x0f ) < ( value & 0x0f ) ){
		CPU_setHalfCarryFlag();
	}
	if( valueA < value ) {
		CPU_setCarryFlag();
	}
	CPU_setSubtractFlag();
}

inline void accumulator_logicalAnd( uint8_t value ){
	cpuRegisters.a = cpuRegisters.a & value;
	if ( cpuRegisters.a == 0 ){
		CPU_setZeroFlag();
	}
}
inline void accumulator_logicalXor( uint8_t value ){
	cpuRegisters.a = cpuRegisters.a ^ value;
	if ( cpuRegisters.a == 0 ){
		CPU_setZeroFlag();
	}
}
inline void accumulator_logicalOr( uint8_t value ){
	cpuRegisters.a = cpuRegisters.a | value;
	if ( cpuRegisters.a == 0 ){
		CPU_setZeroFlag();
	}
}

inline void accumulator_compare( uint8_t value ){
	if( ( cpuRegisters.a & 0x0f ) < ( value & 0x0f ) ){
		CPU_setHalfCarryFlag();
	}
	if( cpuRegisters.a < value ) {
		CPU_setCarryFlag();
	}
	CPU_setSubtractFlag();
	if( cpuRegisters.a == value){
		CPU_setZeroFlag();
	} else {
		CPU_clearZeroFlag();
	}
}

inline void stack_pop( uint16_t* targetRegister ){
	*targetRegister = MMU_readWord( cpuRegisters.sp );
	cpuRegisters.sp = cpuRegisters.sp + 2;
}
inline void stack_push( uint16_t valueRegister ){
	MMU_loadWord( cpuRegisters.sp, valueRegister );
	cpuRegisters.sp = cpuRegisters.sp - 2;
}
inline void stack_restart( uint8_t address ){
	stack_push( cpuRegisters.pc );
	cpuRegisters.pc = address;
}
inline void stack_addDirectByteToSP(){
	uint8_t value = MMU_readByte( cpuRegisters.pc + 1 );
	if( ( ( cpuRegisters.sp & 0x0fff ) + ( value & 0x0fff ) ) &0x1000 ){
		CPU_setHalfCarryFlag();
	}
	cpuRegisters.sp = cpuRegisters.sp + value;
	if( cpuRegisters.sp < value ){
		CPU_setCarryFlag();
	}
}
inline void stack_load_HL_SPWithDirectByteOffset(){
	uint8_t value = MMU_readByte( cpuRegisters.pc + 1 );
	uint16_t sp = cpuRegisters.sp;
	if( ( ( sp & 0x0fff ) + ( value & 0x0fff ) ) &0x1000 ){
		CPU_setHalfCarryFlag();
	} else {
		CPU_clearHalfCarryFlag();
	}
	sp = sp + value;
	if( sp < value ){
		CPU_setCarryFlag();
	} else {
		CPU_clearCarryFlag();
	}
	cpuRegisters.hl = sp;
}
inline void stack_load_SP_HL(){
	cpuRegisters.hl = cpuRegisters.sp;
}
inline void stack_return( flagConditional condition ){
	if( condition ){
		stack_pop( &cpuRegisters.pc );
	}
}
inline void stack_call( flagConditional condition ){
	if( condition ){
		stack_push( cpuRegisters.pc + 1 );
		cpuRegisters.pc = MMU_readWord( cpuRegisters.pc +1 );
	}
}

inline bool jump_relativeByte( flagConditional condition ){
	if( condition ){
		cpuRegisters.pc = cpuRegisters.pc + (int8_t)MMU_readByte( cpuRegisters.pc + 1 );
		return true;
	}
	return false;
}
inline bool jump_toAddressWord( flagConditional condition ){
	if( condition ){
		cpuRegisters.pc = MMU_readWord( cpuRegisters.pc + 1 );
		return true;
	}
	return false;
}
inline bool jump_toHL(){
	cpuRegisters.pc = cpuRegisters.hl;
	return true;
}
inline void shift_memory( direction leftOrRight, significantBitPolicy plan ){
    uint8_t memoryGrabber = MMU_readByte( cpuRegisters.hl );
    shift( &memoryGrabber, leftOrRight, plan );
    MMU_loadByte( cpuRegisters.hl, memoryGrabber );
}
inline void shift( uint8_t* value, direction leftOrRight, significantBitPolicy plan ){
    if( leftOrRight == LEFT ){
        uint8_t carry = *value & 0x80;
        *value = *value << 1;
        if( plan == RESET_SIGNIFICANT_BIT ){
            *value = *value & 0xfe;
        }
        if( carry ){
            CPU_setCarryFlag();
        } else{
            CPU_clearCarryFlag();
        }
    } else{
        uint8_t carry = *value & 0x01;
        *value = *value >> 1;
        if( plan == RESET_SIGNIFICANT_BIT ){
            *value = *value & 0x7F;
        }
        if( carry ){
            CPU_setCarryFlag();
        } else{
            CPU_clearCarryFlag();
        }
    }
}
inline void swapMemoryNibbles(){
    uint8_t memoryGrabber = MMU_readByte( cpuRegisters.hl );
    swapNibbles( &memoryGrabber );
    MMU_loadByte( cpuRegisters.hl, memoryGrabber );
}
inline void swapNibbles( uint8_t* value ){
    uint8_t mostSignificantNibble = *value & 0xf0;
    uint8_t leastSignificantNibble = *value & 0x0f;
    *value = mostSignificantNibble | leastSignificantNibble;
}
inline void bit_read( bitmask targetBit, uint8_t* targetByte ){
	if( (*targetByte & targetBit) == 0 ){
		CPU_setZeroFlag();
	} else {
		CPU_clearZeroFlag();
	}

}
inline void bit_set( bitmask targetBit, uint8_t* targetByte ){
	*targetByte = *targetByte | targetBit;
}
inline void bit_reset( bitmask targetBit, uint8_t* targetByte ){
	*targetByte = *targetByte & !targetBit;
}


inline void bit_memoryRead( bitmask targetBit ){
    uint8_t memoryGrabber = MMU_readByte( cpuRegisters.hl );
    bit_read( targetBit, &memoryGrabber );
    MMU_loadByte( cpuRegisters.hl, memoryGrabber );
}
inline void bit_memorySet( bitmask targetBit ){
    uint8_t memoryGrabber = MMU_readByte( cpuRegisters.hl );
    bit_set( targetBit, &memoryGrabber );
    MMU_loadByte( cpuRegisters.hl, memoryGrabber );
}
inline void bit_memoryReset( bitmask targetBit ){
    uint8_t memoryGrabber = MMU_readByte( cpuRegisters.hl );
    bit_reset( targetBit, &memoryGrabber );
    MMU_loadByte( cpuRegisters.hl, memoryGrabber );
}
