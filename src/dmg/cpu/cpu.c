#include "registers.h"
#include "cpu.h"

DmgRegisters registers;

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
