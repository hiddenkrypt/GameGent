#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "registers.h"
#include "opcodes.h"
#include "../mmu/mmu.h"
#include "../dmg.h"
#include "cpu.h"
#include "cpuInstructions.h"

DmgRegisters cpuRegisters;
static const uint8_t PREFIX_INDICATOR = 0xCB;

/** \brief return the current instruction
 * The fetch and decode steps of the fetch-decode-execute cycle. Finds the current instruction
 * opcode in DMG memory, and returns the appropriate instruction object.
 * Will increment the CPU PC register if a prefix codepoint is found.
 * \return instruction the instruction struct representing the current instruction.
 */
static instruction fetchDecode(){
	uint8_t opcode = MMU_readByte( cpuRegisters.pc );
	if ( opcode != PREFIX_INDICATOR ){
		return codeTable[ opcode ];
	} else {
		cpuRegisters.pc++;
		opcode = MMU_readByte( cpuRegisters.pc );
		return prefixCodeTable[ opcode ];
	}
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
	if( currentInstruction.cycles == 0){
		char errorMessage[100];
		sprintf(errorMessage, "Instruction %#x not found in code table!", MMU_readByte( cpuRegisters.pc ));
		CPU_crash(errorMessage);
	}
	executeInstruction( currentInstruction );
	cpuRegisters.pc++;
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
	printf( reason );
	printf( "\n\n   register dump \n" );
	printf( "   -------------\n" );
	printf( " A |  %#x  |  %#x  | F\n", cpuRegisters.a, cpuRegisters.f );
	printf( " B |  %#x  |  %#x  | C\n", cpuRegisters.bc );
	printf( " D |  %#x  |  %#x  | E\n", cpuRegisters.de );
	printf( " H |  %#x  |  %#x  | L\n", cpuRegisters.hl );
	printf( "   -------------\n");
	printf( "PC |   %#06x  |\n", cpuRegisters.pc );
	printf( "   -------------\n");
	printf( "SP |   %#06x  |\n", cpuRegisters.sp );
	printf( "   -------------\n");
	printf( "  IME: %d \n", cpuRegisters.ime );
}
