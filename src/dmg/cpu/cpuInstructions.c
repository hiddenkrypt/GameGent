#include "registers.h"
#include "opcodes.h"
#include "../mmu/mmu.h"
#include "cpuInstructions.h"

#define NO_CARRY false
#define WITH_CARRY true
#define THROUGH_CARRY true
#define LEFT true
#define RIGHT false

void cpu_noop(){}
void cpu_stop(){}
void cpu_halt(){}
void cpu_setCarryFlag(){}
void cpu_flipCarryFlag(){}
void cpu_enableInterrupts(){}
void cpu_disableInterrupts(){}

void load_16bitRegister_DirectWord( register16 targetRegister ){}
void load_8bitRegister_DirectByte( register8 targetRegister ){}
void load_8bitRegister_MemoryAtRegisterValue( register8 targetRegister, register16 address ){}
void load_8bitRegister_8bitRegister( register8 targetRegister, register8 dataRegister ){}
void load_memory_directByte(){} //ld(HL)d8
void load_memoryAtRegisterValue_8bitRegisterData( register16 address, register8 dataRegister ){}
void load_memoryAtDirectWord_16bitRegister(){} //put SP in memory at direct addr
void load_memoryAtDirectWord_A(){}
void load_memoryHighDirectOffset_A(){}
void load_memoryHighRegisterOffset_A(){}//load(ff00+c),a
void load_A_MemoryAtDirectWord(){}
void load_A_MemoryHighWithDirectByteOffset(){} //load a,ff00+d8
void load_A_MemoryHighWithRegisterByteOffset(){} //load a,c+ff00

void increment_16bitRegister( register16 targetRegister ){}
void decrement_16bitRegister( register16 targetRegister ){}
void increment_8bitRegister( register8 targetRegister ){}
void decrement_8bitRegister( register8 targetRegister ){}
void increment_memoryValue(){} //inc(HL)
void decrement_memoryValue(){} //dec(HL)

void rotate_8bitRegister( register8 targetRegister, bool left, bool throughCarry ){}

void accumulator_add_16bitRegister( register16 valueRegister ){}
void accumulator_add_8bitRegister( register8 valueRegister, bool carry ){}
void accumulator_add_memoryValue( bool carry ){} //a+=(HL)
void accumulator_add_directByte( bool carry ){}
void accumulator_decimalAdjustment(){}
void accumulator_complement(){}
void accumulator_sub_memoryValue( bool carry ){}
void accumulator_sub_8bitRegister( register8 valueRegister, bool carry ){}
void accumulator_sub_directByte(){}
void accumulator_and_8bitRegister( register8 valueRegister ){}
void accumulator_and_memoryValue(){}
void accumulator_and_directByte(){}
void accumulator_xor_8bitRegister( register8 valueRegister ){}
void accumulator_xor_memoryValue(){}
void accumulator_xor_directByte(){}
void accumulator_or_8bitRegister( register8 valueRegister ){}
void accumulator_or_memoryValue(){}
void accumulator_or_directByte(){}
void accumulator_cp_8bitRegister( register8 valueRegister ){}
void accumulator_cp_memoryValue(){}
void accumulator_cp_directByte(){}

void stack_pop( register16 targetRegister ){}
void stack_push( register16 valueRegister ){}
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
	switch( opcode.codePoint ){
		case 0x00:
			cpu_noop();
			break;
		case 0x01:
			load_16bitRegister_DirectWord( BC );
			break;
		case 0x02:
			load_memoryAtRegisterValue_8bitRegisterData( BC, A );
			break;
		case 0x03:
			increment_16bitRegister( BC );
			break;
		case 0x04:
			increment_8bitRegister( B );
			break;
		case 0x05:
			decrement_8bitRegister( B );
			break;
		case 0x06:
			load_8bitRegister_DirectByte( B );
			break;
		case 0x07:
			rotate_8bitRegister( A, LEFT, NO_CARRY);
			break;
		case 0x08:
			load_memoryAtDirectWord_16bitRegister(); //add sp
			break;
		case 0x09:
			accumulator_add_16bitRegister( BC );
			break;
		case 0x0a:
			load_8bitRegister_MemoryAtRegisterValue( A, BC );
			break;
		case 0x0b:
			decrement_16bitRegister( BC );
			break;
		case 0x0c:
			increment_8bitRegister( C );
			break;
		case 0x0d:
			decrement_8bitRegister( C );
			break;
		case 0x0e:
			load_8bitRegister_DirectByte( C );
			break;
		case 0x0f:
			rotate_8bitRegister( A, RIGHT, NO_CARRY );
			break;
		case 0x10:
			cpu_stop();
			break;
		case 0x11:
			load_16bitRegister_DirectWord( DE );
			break;
		case 0x12:
			load_memoryAtRegisterValue_8bitRegisterData( DE, A );
			break;
		case 0x13:
			increment_16bitRegister( DE );
			break;
		case 0x14:
			increment_8bitRegister( D );
			break;
		case 0x15:
			decrement_8bitRegister( D );
			break;
		case 0x16:
			load_8bitRegister_DirectByte( D );
			break;
		case 0x17:
			rotate_8bitRegister( A, LEFT, THROUGH_CARRY );
			break;
		case 0x18:
			jump_relativeByte( CONDITION_ALWAYS );
			break;
		case 0x19:
			accumulator_add_16bitRegister( DE );
			break;
		case 0x1a:
			load_8bitRegister_MemoryAtRegisterValue( A, DE );
			break;
		case 0x1b:
			decrement_16bitRegister( DE );
			break;
		case 0x1c:
			increment_8bitRegister( E );
			break;
		case 0x1d:
			decrement_8bitRegister( E );
			break;
		case 0x1e:
			load_8bitRegister_DirectByte( E );
			break;
		case 0x1f:
			rotate_8bitRegister( A, RIGHT, THROUGH_CARRY );
			break;
		case 0x20:
			jump_relativeByte( CONDITION_NO_ZERO );
			break;
		case 0x21:
			load_16bitRegister_DirectWord( HL );
			break;
		case 0x22:
			load_memoryAtRegisterValue_8bitRegisterData( HL, A );
			increment_16bitRegister( HL );
			break;
		case 0x23:
			increment_16bitRegister( HL );
			break;
		case 0x24:
			increment_8bitRegister( H );
			break;
		case 0x25:
			decrement_8bitRegister( H );
			break;
		case 0x26:
			load_8bitRegister_DirectByte( H );
			break;
		case 0x27:
			accumulator_decimalAdjustment();
			break;
		case 0x28:
			jump_relativeByte( CONDITION_ZERO );
			break;
		case 0x29:
			accumulator_add_16bitRegister( HL );
			break;
		case 0x2a:
			load_8bitRegister_MemoryAtRegisterValue( A, HL );
			increment_16bitRegister( HL );
			break;
		case 0x2b:
			decrement_16bitRegister( HL );
			break;
		case 0x2c:
			increment_8bitRegister( L );
			break;
		case 0x2d:
			decrement_8bitRegister( L );
			break;
		case 0x2e:
			load_8bitRegister_DirectByte( L );
			break;
		case 0x2f:
			accumulator_complement();
			break;
		case 0x30:
			jump_relativeByte( CONDITION_NO_CARRY );
			break;
		case 0x31:
			load_16bitRegister_DirectWord( SP );
			break;
		case 0x32:
			load_memoryAtRegisterValue_8bitRegisterData( HL, A );
			decrement_16bitRegister( HL );
			break;
		case 0x33:
			increment_16bitRegister( SP );
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
			jump_relativeByte( C );
			break;
		case 0x39:
			accumulator_add_16bitRegister( SP );
			break;
		case 0x3a:
			load_8bitRegister_MemoryAtRegisterValue( A, HL );
			decrement_16bitRegister( HL );
			break;
		case 0x3b:
			decrement_16bitRegister( SP );
			break;
		case 0x3c:
			increment_8bitRegister( A );
			break;
		case 0x3d:
			decrement_8bitRegister( A );
			break;
		case 0x3e:
			load_8bitRegister_DirectByte( A );
			break;
		case 0x3f:
			cpu_flipCarryFlag();
			break;
		case 0x40:
			cpu_noop();
			break;
		case 0x41:
			load_8bitRegister_8bitRegister( B, C );
			break;
		case 0x42:
			load_8bitRegister_8bitRegister( B, D );
			break;
		case 0x43:
			load_8bitRegister_8bitRegister( B, E );
			break;
		case 0x44:
			load_8bitRegister_8bitRegister( B, H );
			break;
		case 0x45:
			load_8bitRegister_8bitRegister( B, L );
			break;
		case 0x46:
			load_8bitRegister_MemoryAtRegisterValue( B, HL );
			break;
		case 0x47:
			load_8bitRegister_8bitRegister( B, A );
			break;
		case 0x48:
			load_8bitRegister_8bitRegister( C, B );
			break;
		case 0x49:
			cpu_noop();
			break;
		case 0x4a:
			load_8bitRegister_8bitRegister( C, D );
			break;
		case 0x4b:
			load_8bitRegister_8bitRegister( C, E );
			break;
		case 0x4c:
			load_8bitRegister_8bitRegister( C, H );
			break;
		case 0x4d:
			load_8bitRegister_8bitRegister( C, L );
			break;
		case 0x4e:
			load_8bitRegister_MemoryAtRegisterValue( C, HL );
			break;
		case 0x4f:
			load_8bitRegister_8bitRegister( C, A );
			break;
		case 0x50:
			load_8bitRegister_8bitRegister( D, B );
			break;
		case 0x51:
			load_8bitRegister_8bitRegister( D, C );
			break;
		case 0x52:
			cpu_noop();
			break;
		case 0x53:
			load_8bitRegister_8bitRegister( D, E );
			break;
		case 0x54:
			load_8bitRegister_8bitRegister( D, H );
			break;
		case 0x55:
			load_8bitRegister_8bitRegister( D, L );
			break;
		case 0x56:
			load_8bitRegister_MemoryAtRegisterValue( D, HL );
			break;
		case 0x57:
			load_8bitRegister_8bitRegister( D, A );
			break;
		case 0x58:
			load_8bitRegister_8bitRegister( E, B );
			break;
		case 0x59:
			load_8bitRegister_8bitRegister( E, C );
			break;
		case 0x5a:
			load_8bitRegister_8bitRegister( E, D );
			break;
		case 0x5b:
			cpu_noop();
			break;
		case 0x5c:
			load_8bitRegister_8bitRegister( E, H );
			break;
		case 0x5d:
			load_8bitRegister_8bitRegister( E, L );
			break;
		case 0x5e:
			load_8bitRegister_MemoryAtRegisterValue( E, HL );
			break;
		case 0x5f:
			load_8bitRegister_8bitRegister( E, A );
			break;
		case 0x60:
			load_8bitRegister_8bitRegister( H, B );
			break;
		case 0x61:
			load_8bitRegister_8bitRegister( H, C );
			break;
		case 0x62:
			load_8bitRegister_8bitRegister( H, D );
			break;
		case 0x63:
			load_8bitRegister_8bitRegister( H, E );
			break;
		case 0x64:
			cpu_noop();
			break;
		case 0x65:
			load_8bitRegister_8bitRegister( H, L );
			break;
		case 0x66:
			load_8bitRegister_MemoryAtRegisterValue( H, HL );
			break;
		case 0x67:
			load_8bitRegister_8bitRegister( H, A );
			break;
		case 0x68:
			load_8bitRegister_8bitRegister( L, B );
			break;
		case 0x69:
			load_8bitRegister_8bitRegister( L, C );
			break;
		case 0x6a:
			load_8bitRegister_8bitRegister( L, D );
			break;
		case 0x6b:
			load_8bitRegister_8bitRegister( L, E );
			break;
		case 0x6c:
			load_8bitRegister_8bitRegister( L, H );
			break;
		case 0x6d:
			cpu_noop();
			break;
		case 0x6e:
			load_8bitRegister_MemoryAtRegisterValue( L, HL );
			break;
		case 0x6f:
			load_8bitRegister_8bitRegister( L, A );
			break;
		case 0x70:
			load_memoryAtRegisterValue_8bitRegisterData( HL, B );
			break;
		case 0x71:
			load_memoryAtRegisterValue_8bitRegisterData( HL, C );
			break;
		case 0x72:
			load_memoryAtRegisterValue_8bitRegisterData( HL, D );
			break;
		case 0x73:
			load_memoryAtRegisterValue_8bitRegisterData( HL, E );
			break;
		case 0x74:
			load_memoryAtRegisterValue_8bitRegisterData( HL, H );
			break;
		case 0x75:
			load_memoryAtRegisterValue_8bitRegisterData( HL, L );
			break;
		case 0x76:
			cpu_halt();
			break;
		case 0x77:
			load_memoryAtRegisterValue_8bitRegisterData( HL, A );
			break;
		case 0x78:
			load_8bitRegister_8bitRegister( A, B );
			break;
		case 0x79:
			load_8bitRegister_8bitRegister( A, C );
			break;
		case 0x7a:
			load_8bitRegister_8bitRegister( A, D );
			break;
		case 0x7b:
			load_8bitRegister_8bitRegister( A, E );
			break;
		case 0x7c:
			load_8bitRegister_8bitRegister( A, H );
			break;
		case 0x7d:
			load_8bitRegister_8bitRegister( A, L );
			break;
		case 0x7e:
			load_8bitRegister_MemoryAtRegisterValue( A, HL );
			break;
		case 0x7f:
			cpu_noop();
			break;
		case 0x80:
			accumulator_add_8bitRegister( B, NO_CARRY );
			break;
		case 0x81:
			accumulator_add_8bitRegister( C, NO_CARRY );
			break;
		case 0x82:
			accumulator_add_8bitRegister( D, NO_CARRY );
			break;
		case 0x83:
			accumulator_add_8bitRegister( E, NO_CARRY );
			break;
		case 0x84:
			accumulator_add_8bitRegister( H, NO_CARRY );
			break;
		case 0x85:
			accumulator_add_8bitRegister( L, NO_CARRY );
			break;
		case 0x86:
			accumulator_add_memoryValue( NO_CARRY );
			break;
		case 0x87:
			accumulator_add_8bitRegister( A, NO_CARRY );
			break;
		case 0x88:
			accumulator_add_8bitRegister( B, WITH_CARRY );
			break;
		case 0x89:
			accumulator_add_8bitRegister( C, WITH_CARRY );
			break;
		case 0x8a:
			accumulator_add_8bitRegister( D, WITH_CARRY );
			break;
		case 0x8b:
			accumulator_add_8bitRegister( E, WITH_CARRY );
			break;
		case 0x8c:
			accumulator_add_8bitRegister( H, WITH_CARRY );
			break;
		case 0x8d:
			accumulator_add_8bitRegister( L, WITH_CARRY );
			break;
		case 0x8e:
			accumulator_add_memoryValue( WITH_CARRY );
			break;
		case 0x8f:
			accumulator_add_8bitRegister( A, WITH_CARRY );
			break;
		case 0x90:
			accumulator_sub_8bitRegister( B, NO_CARRY );
			break;
		case 0x91:
			accumulator_sub_8bitRegister( C, NO_CARRY );
			break;
		case 0x92:
			accumulator_sub_8bitRegister( D, NO_CARRY );
			break;
		case 0x93:
			accumulator_sub_8bitRegister( E, NO_CARRY );
			break;
		case 0x94:
			accumulator_sub_8bitRegister( H, NO_CARRY );
			break;
		case 0x95:
			accumulator_sub_8bitRegister( L, NO_CARRY );
			break;
		case 0x96:
			accumulator_sub_memoryValue( NO_CARRY );
			break;
		case 0x97:
			accumulator_sub_8bitRegister( A, NO_CARRY );
			break;
		case 0x98:
			accumulator_sub_8bitRegister( B, WITH_CARRY );
			break;
		case 0x99:
			accumulator_sub_8bitRegister( C, WITH_CARRY );
			break;
		case 0x9a:
			accumulator_sub_8bitRegister( D, WITH_CARRY );
			break;
		case 0x9b:
			accumulator_sub_8bitRegister( E, WITH_CARRY );
			break;
		case 0x9c:
			accumulator_sub_8bitRegister( H, WITH_CARRY );
			break;
		case 0x9d:
			accumulator_sub_8bitRegister( L, WITH_CARRY );
			break;
		case 0x9e:
			accumulator_sub_memoryValue( WITH_CARRY );
			break;
		case 0x9f:
			accumulator_sub_8bitRegister( A, WITH_CARRY );
			break;
		case 0xa0:
			accumulator_and_8bitRegister( B );
			break;
		case 0xa1:
			accumulator_and_8bitRegister( C );
			break;
		case 0xa2:
			accumulator_and_8bitRegister( D );
			break;
		case 0xa3:
			accumulator_and_8bitRegister( E );
			break;
		case 0xa4:
			accumulator_and_8bitRegister( H );
			break;
		case 0xa5:
			accumulator_and_8bitRegister( L );
			break;
		case 0xa6:
			accumulator_and_memoryValue();
			break;
		case 0xa7:
			accumulator_and_8bitRegister( A );
			break;
		case 0xa8:
			accumulator_xor_8bitRegister( B );
			break;
		case 0xa9:
			accumulator_xor_8bitRegister( C );
			break;
		case 0xaa:
			accumulator_xor_8bitRegister( D );
			break;
		case 0xab:
			accumulator_xor_8bitRegister( E );
			break;
		case 0xac:
			accumulator_xor_8bitRegister( H );
			break;
		case 0xad:
			accumulator_xor_8bitRegister( L );
			break;
		case 0xae:
			accumulator_xor_memoryValue();
			break;
		case 0xaf:
			accumulator_xor_8bitRegister( A );
			break;
		case 0xb0:
			accumulator_or_8bitRegister( B );
			break;
		case 0xb1:
			accumulator_or_8bitRegister( C );
			break;
		case 0xb2:
			accumulator_or_8bitRegister( D );
			break;
		case 0xb3:
			accumulator_or_8bitRegister( E );
			break;
		case 0xb4:
			accumulator_or_8bitRegister( H );
			break;
		case 0xb5:
			accumulator_or_8bitRegister( L );
			break;
		case 0xb6:
			accumulator_or_memoryValue();
			break;
		case 0xb7:
			accumulator_or_8bitRegister( A );
			break;
		case 0xb8:
			accumulator_cp_8bitRegister( B );
			break;
		case 0xb9:
			accumulator_cp_8bitRegister( C );
			break;
		case 0xba:
			accumulator_cp_8bitRegister( D );
			break;
		case 0xbb:
			accumulator_cp_8bitRegister( E );
			break;
		case 0xbc:
			accumulator_cp_8bitRegister( H );
			break;
		case 0xbd:
			accumulator_cp_8bitRegister( L );
			break;
		case 0xbe:
			accumulator_cp_memoryValue();
			break;
		case 0xbf:
			accumulator_cp_8bitRegister( A );
			break;
		case 0xc0:
			stack_return( CONDITION_NO_ZERO );
			break;
		case 0xc1:
			stack_pop( BC );
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
			stack_push( BC );
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
			stack_pop( DE );
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
			stack_push( DE );
			break;
		case 0xd6:
			accumulator_sub_directByte( NO_CARRY );
			break;
		case 0xd7:
			stack_reset( 0x10 );
			break;
		case 0xd8:
			stack_return( C );
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
			stack_call( C );
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
			stack_pop( HL );
			break;
		case 0xe2:
			load_memoryHighRegisterOffset_A(); //addr=ff00+c
			break;
		case 0xe3:
			break;
		case 0xe4:
			break;
		case 0xe5:
			stack_push( HL );
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
			stack_pop( AF );
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
			stack_push( AF );
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
