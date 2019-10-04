#include <stdint.h>
#include <stdbool.h>
#include "registers.h"
#include "opcodes.h"
#include "MMU.h"
#include "cpu.h"

DmgRegisters registers;
static const uint8_t PREFIX_INDICATOR = 0xCB;

static instruction fetchDecode();


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
    //executeInstruction( currentInstruction );
    registers.PC++;
}

/** \brief return the current instruction
 * The fetch and decode steps of the fetch-decode-execute cycle. Finds the current instruction
 * opcode in DMG memory, and returns the appropriate instruction object.
 * Will increment the CPU PC register if a prefix codepoint is found.
 * \return instruction the instruction struct representing the current instruction.
 */
static instruction fetchDecode(){
    uint8_t opcode = MMU_readByte( registers.PC );
    if ( opcode != PREFIX_INDICATOR ){
        return codeTable[ opcode ];
    } else {
        registers.PC++;
        opcode = MMU_readByte( registers.PC );
        return prefixCodeTable[ opcode ];
    }
}
