
#include "registers.h"
#include "opcodes.h"
#include "../mmu/mmu.h"
#include "cpuInstructions.h"
void cpu_noop(){}
void cpu_stop(){}
void cpu_halt(){}
void cpu_setCarryFlag(){}
void cpu_flipCarryFlag(){}
void load_16bitRegister_DirectWord( register16 targetRegister ){}
void load_8bitRegister_DirectByte( register8 targetRegister ){}
void load_8bitRegister_MemoryAtRegisterValue( register8 targetRegister, register16 address ){}
void load_8bitRegister_8bitRegister( register8 targetRegister, register8 dataRegister ){}
void load_memory_directByte(){} //ld(HL)d8
void load_memoryAtRegisterValue_8bitRegisterData( register16 address, register8 dataRegister ){}
void load_memoryAtDirectWord_16bitRegister(){} //put SP in memory at direct addr
void increment_16bitRegister( register16 targetRegister ){}
void decrement_16bitRegister( register16 targetRegister ){}
void increment_8bitRegister( register8 targetRegister ){}
void decrement_8bitRegister( register8 targetRegister ){}
void increment_memoryValue(){} //inc(HL)
void decrement_memoryValue(){} //dec(HL)
void rotate_8bitRegister( register8 targetRegister, bool left, bool throughCarry ){}
void add_16bitRegister( register16 valueRegister ){}
void add_8bitRegister( register8 valueRegister, bool carry ){}
void add_memoryValue( bool carry ){} //a+=(HL)
void accumulator_decimalAdjustment(){}
void accumulator_complement(){}

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
			rotate_8bitRegister( A, true, false);
			break;
		case 0x08:
			load_memoryAtDirectWord_16bitRegister(); //add sp
			break;
		case 0x09:
			add_16bitRegister( BC );
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
			rotate_8bitRegister( A, false, false);
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
			rotate_8bitRegister( A, true, true );
			break;
		case 0x18:
			/** @todo jump relative 8 bit data **/ break;
		case 0x19:
			add_16bitRegister( DE );
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
			rotate_8bitRegister( A, false, true );
			break;
		case 0x20:
			/** @todo jump NZ relative 8 bit data **/break;
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
			accumulator_decimalAdjustment(); /** DAA */
			break;
		case 0x28:
			/** @todo jump zero, relative 8 **/
			break;
		case 0x29:
			add_16bitRegister( HL );
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
			accumulator_complement(); /** CPL */
			break;
		case 0x30:
			/** @todo Jump  No Carry, relative8 */
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
			/** @todo jump carry relative 8 **/
			break;
		case 0x39:
			add_16bitRegister( SP );
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
			add_8bitRegister( B, false );
			break;
		case 0x81:
			add_8bitRegister( C, false );
			break;
		case 0x82:
			add_8bitRegister( D, false );
			break;
		case 0x83:
			add_8bitRegister( E, false );
			break;
		case 0x84:
			add_8bitRegister( H, false );
			break;
		case 0x85:
			add_8bitRegister( L, false );
			break;
		case 0x86:
			add_memoryValue( false );
			break;
		case 0x87:
			add_8bitRegister( A, false );
			break;
		case 0x88:
			add_8bitRegister( B, true );
			break;
		case 0x89:
			add_8bitRegister( C, true );
			break;
		case 0x8a:
			add_8bitRegister( D, true );
			break;
		case 0x8b:
			add_8bitRegister( E, true );
			break;
		case 0x8c:
			add_8bitRegister( H, true );
			break;
		case 0x8d:
			add_8bitRegister( L, true );
			break;
		case 0x8e:
			add_memoryValue( true );
			break;
		case 0x8f:
			add_8bitRegister( A, true );
			break;
		case 0x90:

			break;
		case 0x91:

			break;
		case 0x92:

			break;
		case 0x93:

			break;
		case 0x94:

			break;
		case 0x95:

			break;
		case 0x96:

			break;
		case 0x97:

			break;
		case 0x98:

			break;
		case 0x99:

			break;
		case 0x9a:

			break;
		case 0x9b:

			break;
		case 0x9c:

			break;
		case 0x9d:

			break;
		case 0x9e:

			break;
		case 0x9f:

			break;
		case 0xa0:

			break;
		case 0xa1:

			break;
		case 0xa2:

			break;
		case 0xa3:

			break;
		case 0xa4:

			break;
		case 0xa5:

			break;
		case 0xa6:

			break;
		case 0xa7:

			break;
		case 0xa8:

			break;
		case 0xa9:

			break;
		case 0xaa:

			break;
		case 0xab:

			break;
		case 0xac:

			break;
		case 0xad:

			break;
		case 0xae:

			break;
		case 0xaf:

			break;
		case 0xb0:

			break;
		case 0xb1:

			break;
		case 0xb2:

			break;
		case 0xb3:

			break;
		case 0xb4:

			break;
		case 0xb5:

			break;
		case 0xb6:

			break;
		case 0xb7:

			break;
		case 0xb8:

			break;
		case 0xb9:

			break;
		case 0xba:

			break;
		case 0xbb:

			break;
		case 0xbc:

			break;
		case 0xbd:

			break;
		case 0xbe:

			break;
		case 0xbf:

			break;
		case 0xc0:

			break;
		case 0xc1:

			break;
		case 0xc2:

			break;
		case 0xc3:

			break;
		case 0xc4:

			break;
		case 0xc5:

			break;
		case 0xc6:

			break;
		case 0xc7:

			break;
		case 0xc8:

			break;
		case 0xc9:

			break;
		case 0xca:

			break;
		case 0xcb:

			break;
		case 0xcc:

			break;
		case 0xcd:

			break;
		case 0xce:

			break;
		case 0xcf:

			break;
		case 0xd0:

			break;
		case 0xd1:

			break;
		case 0xd2:

			break;
		case 0xd3:

			break;
		case 0xd4:

			break;
		case 0xd5:

			break;
		case 0xd6:

			break;
		case 0xd7:

			break;
		case 0xd8:

			break;
		case 0xd9:

			break;
		case 0xda:

			break;
		case 0xdb:

			break;
		case 0xdc:

			break;
		case 0xdd:

			break;
		case 0xde:

			break;
		case 0xdf:

			break;
		case 0xe0:

			break;
		case 0xe1:

			break;
		case 0xe2:

			break;
		case 0xe3:

			break;
		case 0xe4:

			break;
		case 0xe5:

			break;
		case 0xe6:

			break;
		case 0xe7:

			break;
		case 0xe8:

			break;
		case 0xe9:

			break;
		case 0xea:

			break;
		case 0xeb:

			break;
		case 0xec:

			break;
		case 0xed:

			break;
		case 0xee:

			break;
		case 0xef:

			break;
		case 0xf0:

			break;
		case 0xf1:

			break;
		case 0xf2:

			break;
		case 0xf3:

			break;
		case 0xf4:

			break;
		case 0xf5:

			break;
		case 0xf6:

			break;
		case 0xf7:

			break;
		case 0xf8:

			break;
		case 0xf9:

			break;
		case 0xfa:

			break;
		case 0xfb:

			break;
		case 0xfc:

			break;
		case 0xfd:

			break;
		case 0xfe:

			break;
		case 0xff:

			break;
	}
}
