#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <conio.h>
#include "../mmu/mmu.h"
#include "registers.h"
#include "cpu.h"
#include "codeTables.h"
#include "debugger.h"

void Debugger_break(){
    system("cls");
	printf( "\n\n   =======BREAK=======\n" );
	printf( "   ------------------------\n" );
	printf( " AF| %#06x |  BC| %#06x |\n", cpuRegisters.af, cpuRegisters.bc );
	printf( " DE| %#06x |  HL| %#06x |\n", cpuRegisters.de, cpuRegisters.hl );
	printf( " PC| %#06x |  SP| %#06x |\n", cpuRegisters.pc, cpuRegisters.sp );
	printf( "   ------------------------\n");
	printf( " memory dump \n");
    uint16_t workAddress = cpuRegisters.pc;
    for( int i = 0 ; i<6; i++ ){
        instruction currentInstruction = codeTable[ MMU_readByte( workAddress ) ];
        printf( "%#06x %s\n", workAddress, currentInstruction.mnemonic );
        workAddress = workAddress + currentInstruction.length;
    }
	printf("what do\n");
	char in;
	in = getch();
	printf("\nok %c\n",in);
}


