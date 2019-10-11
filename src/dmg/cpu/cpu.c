#include <stdint.h>
#include <stdbool.h>
#include "registers.h"
#include "opcodes.h"
#include "MMU.h"
#include "dmg.h"
#include "cpu.h"

#include <stdio.h>

DmgRegisters registers;
static const uint8_t PREFIX_INDICATOR = 0xCB;

/** \brief return the current instruction
 * The fetch and decode steps of the fetch-decode-execute cycle. Finds the current instruction
 * opcode in DMG memory, and returns the appropriate instruction object.
 * Will increment the CPU PC register if a prefix codepoint is found.
 * \return instruction the instruction struct representing the current instruction.
 */
static instruction fetchDecode(){
    printf("fetch %#x\n",registers.PC);
    uint8_t opcode = MMU_readByte( registers.PC );
    if ( opcode != PREFIX_INDICATOR ){
        return codeTable[ opcode ];
    } else {
        registers.PC++;
        opcode = MMU_readByte( registers.PC );
        return prefixCodeTable[ opcode ];
    }
}


/** \brief sets up CPU initial state
 * configures internal registers to initial state, serving as a CPU restart option
 * \todo pick state based on presence of bootloader rom.
 */
void CPU_init(){ //serves as a restart
    registers.af = 0x0000;
    registers.bc = 0x0000;
    registers.de = 0x0000;
    registers.hl = 0x0000;
    registers.PC = 0x0000;
    registers.SP = 0xFFFE;
}



/** \brief CPU fetch-decode-execute step
 * Sends the CPU through one instruction cycle. Fetch is handed off to the Opcodes module.
 */
void CPU_tick(){
    instruction currentInstruction = fetchDecode();
    if( currentInstruction.ticks == 0){
        char errorMessage[100];
        sprintf(errorMessage, "Instruction %#x not found in code table!", MMU_readByte( registers.PC ));
        CPU_crash(errorMessage);
    }
    /** \todo: executeInstruction( currentInstruction );*/
    registers.PC++;
}

void CPU_crash(char* reason){
    DMG_haltEmulation();
    printf(reason);
    printf("\n\n   register dump \n");
    printf("   -------------\n");
    printf(" A |  %#x  |  %#x  | F\n", registers.a, registers.f);
    printf(" B |  %#x  |  %#x  | C\n", registers.bc);
    printf(" D |  %#x  |  %#x  | E\n", registers.de);
    printf(" H |  %#x  |  %#x  | L\n", registers.hl);
    printf("   -------------\n");
    printf("PC |   %#06x  |\n", registers.PC);
    printf("   -------------\n");
    printf("SP |   %#06x  |\n", registers.SP);
    printf("   -------------\n");
}
