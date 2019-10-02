#include "registers.h"
#include "cpu.h"

DmgRegisters registers;

void CPU_init(){ //serves as a restart

    registers.af = 0x0000;
    registers.bc = 0x0000;
    registers.de = 0x0000;
    registers.hl = 0x0000;
    registers.PC = 0x0000;
    registers.SP = 0xFFFE;
}
