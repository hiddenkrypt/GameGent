#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "../../settings.h"
#include "../mmu/mmu.h"
#include "../dmg.h"
#include "registers.h"
#include "opcodes.h"
#include "cpuInstructions.h"
#include "codeTables.h"
#include "cpu.h"

/** @todo cpu halt and stop
 * @todo timings
 * @todo predictable flags
 * @todo interrupts
 *
 */

DmgRegisters cpuRegisters;
static const uint8_t PREFIX_INDICATOR = 0xCB;
static void cpuInstructionDebug( instruction currentInstruction ){
//	if ( cpuRegisters.pc > 0x2f ){
//        CPU_crash( "force crash at  for Debug" );
//	}
	printf("%#06x|  %#04x %s", cpuRegisters.pc, currentInstruction.codePoint, currentInstruction.mnemonic);
	if(currentInstruction.length > 1 ){
		printf(" %s",currentInstruction.arg1);
	}
	if(currentInstruction.length > 2 ){
		printf(" %s",currentInstruction.arg2);
	}
	printf("\n");
}
/** \brief return the current instruction
 * The fetch and decode steps of the fetch-decode-execute cycle. Finds the current instruction
 * opcode in DMG memory, and returns the appropriate instruction object.
 * Will increment the CPU PC register if a prefix codepoint is found.
 * \return instruction the instruction struct representing the current instruction.
 */
static instruction fetchDecode(){
	uint8_t opcode = MMU_readByte( cpuRegisters.pc );
	instruction currentInstruction;

	if ( opcode != PREFIX_INDICATOR ){
		currentInstruction = codeTable[ opcode ];
	} else {
		opcode = MMU_readByte( cpuRegisters.pc+1 );
		currentInstruction = prefixCodeTable[ opcode ];
	}

	if( Settings_getDebugFlag() ){
		cpuInstructionDebug( currentInstruction );
	}
	return currentInstruction;
}


/** \brief sets up CPU initial state
 * configures internal registers to initial state, serving as a CPU restart option
 * \todo pick state based on presence or absence of bootloader rom.
 */
void CPU_init(){ //serves as a restart
	cpuRegisters.af = 0x0000;
	cpuRegisters.bc = 0x0000;
	cpuRegisters.de = 0x0000;
	cpuRegisters.hl = 0x0000;
	cpuRegisters.pc = 0x0000;
	cpuRegisters.sp = 0x0000;
	cpuRegisters.ime = true;
}



/** \brief CPU fetch-decode-execute step
 * Sends the CPU through one instruction cycle. Fetch is handed off to the Opcodes module.
 */
void CPU_tick(){
	instruction currentInstruction = fetchDecode();
	executeInstruction( currentInstruction );
	cpuRegisters.pc = cpuRegisters.pc + currentInstruction.length;
}

/** \brief stop the cpu and print out some debug information
 *
 * Called whenever something goes wrong and is caught by checking code,
 * this function stops the emulation core and prints out debug info
 * info includes a reason given by the calling code, and a dump of current
 * cpu register values.
 *
 * @todo include a disassembled set of recent instructions
 *
 * \param reason - an explanation of the crash, if possible, to be printed with the debug info
 */
void CPU_crash( char* reason ){
	DMG_stopEmulation();
	printf( "\n\n=======CPU CRASH=======\n" );
	printf( reason );
	printf( "\n\n   register dump \n" );
	printf( "   -------------------\n" );
	printf( " A |  %#04x  |  %#04x  | F\n", cpuRegisters.a, cpuRegisters.f );
	printf( " B |  %#04x  |  %#04x  | C\n", cpuRegisters.b, cpuRegisters.c );
	printf( " D |  %#04x  |  %#04x  | E\n", cpuRegisters.d, cpuRegisters.e );
	printf( " H |  %#04x  |  %#04x  | L\n", cpuRegisters.h, cpuRegisters.l );
	printf( "   -------------------\n");
	printf( "PC | %#06x | %#06x | SP\n", cpuRegisters.pc, cpuRegisters.sp  );
	printf( "   -------------------\n");
	printf( "  IME: %d \n\n", cpuRegisters.ime );
	printf( " memory dump \n");
	uint16_t position = cpuRegisters.pc-5;
	if( position < 0 ){ position = 0; }
	for(uint16_t i = position; i < cpuRegisters.pc+10; i++){
		if( cpuRegisters.pc == i){
			printf("PC==>");
		}else{
			printf("     ");
		}
		printf("%#06x -- %#04x\n", i, MMU_readByte( i ));
	}
}

void CPU_noop(){}
void CPU_stop(){
/** per gbcpuman.pdf
 * The STOP command halts the GameBoy processor and screen until
 * any button is pressed. The GB and GBP screen goes white with
 * a single dark horizontal line. The GBC screen goes black.
 */
}
void CPU_halt(){
/**
 * stops system clock until the next interrupt.
 * after interrupt service, execution begins right after halt opcode
 * if interrupts are disabled, command gets really funky: "the halt bug", and takes special consideration.
 */
}
void CPU_setCarryFlag(){
	cpuRegisters.f = cpuRegisters.f | FLAG_CARRY;
}
void CPU_clearCarryFlag(){
	cpuRegisters.f = cpuRegisters.f & (~FLAG_CARRY);
}
void CPU_flipCarryFlag(){
	cpuRegisters.f = cpuRegisters.f ^ FLAG_CARRY;
}
bool CPU_getCarryFlag(){
	return cpuRegisters.f & FLAG_CARRY;
}



void CPU_setZeroFlag(){
	cpuRegisters.f = cpuRegisters.f | FLAG_ZERO;
}
void CPU_clearZeroFlag(){
	cpuRegisters.f = cpuRegisters.f & (~FLAG_ZERO);
}
bool CPU_getZeroFlag(){
	return cpuRegisters.f & FLAG_ZERO;
}



void CPU_setHalfCarryFlag(){
	cpuRegisters.f = cpuRegisters.f | FLAG_HALFCARRY;
}
void CPU_clearHalfCarryFlag(){
	cpuRegisters.f = cpuRegisters.f & (~FLAG_HALFCARRY);
}
bool CPU_getHalfCarryFlag(){
	return cpuRegisters.f & FLAG_HALFCARRY;
}



void CPU_setSubtractFlag(){
	cpuRegisters.f = cpuRegisters.f | FLAG_SUBTRACT;
}
void CPU_clearSubtractFlag(){
	cpuRegisters.f = cpuRegisters.f & (~FLAG_SUBTRACT);
}
bool CPU_getSubtractFlag(){
	return cpuRegisters.f & FLAG_SUBTRACT;
}



void CPU_enableInterrupts(){
	cpuRegisters.ime = true;
}
void CPU_disableInterrupts(){
	cpuRegisters.ime = false;
}
