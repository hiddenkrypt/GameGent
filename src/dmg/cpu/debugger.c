#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "../mmu/mmu.h"
#include "registers.h"
#include "cpu.h"
#include "codeTables.h"
#include "debugger.h"
char* stringifyInstruction( uint16_t addr, instruction details );
void Debugger_break(){
    system("cls");
	printf( "\n\n   =======BREAK=======\n" );
	printf( "   ------------------------\n" );
	printf( " AF| %#06x |  BC| %#06x |\n", cpuRegisters.af, cpuRegisters.bc );
	printf( " DE| %#06x |  HL| %#06x |\n", cpuRegisters.de, cpuRegisters.hl );
	printf( " PC| %#06x |  SP| %#06x |\n", cpuRegisters.pc, cpuRegisters.sp );
	printf( "   ------------------------\n");
	printf( " Code: \n");
    uint16_t workAddress = cpuRegisters.pc;
    for( int i = 0 ; i<6; i++ ){
        instruction currentInstruction = codeTable[ MMU_readByte( workAddress ) ];
        char* instructionString = stringifyInstruction( workAddress + 1, currentInstruction );
        printf( "%#06x %s\n", workAddress, instructionString );
        workAddress = workAddress + currentInstruction.length;
    }
    printf("raw memdump\n");

    for( int i = 0 ; i<10; i++ ){
        printf( "[%#06x] %#04x \n", cpuRegisters.pc+i, MMU_readByte( cpuRegisters.pc+i ) );
    }
	printf("what do\n");
	char in;
	in = getch();
	printf("\nok %c\n",in);
}

char* stringifyInstruction( uint16_t addr, instruction details ){
    char* buff = (char*) malloc( 30 * sizeof(char) );
    char* arg1String = (char*) malloc( 10 * sizeof(char) );
    char* arg2String = (char*) malloc( 14 * sizeof(char) );
    buff[0] = '\0';
    arg1String[0] = '\0';
    arg2String[0] = '\0';
    if( strcmp( details.arg1, "" ) != 0 ){
        if( strcmp( details.arg1, "(a16)" ) == 0 ){
            sprintf( arg1String, "(%#06x)", MMU_readWord( addr ) );
            addr = addr + 2;
        } else if( strcmp( details.arg1, "d8" ) == 0){
            sprintf( arg1String, "%#04x", MMU_readByte( addr ) );
            addr = addr + 1;
        } else if( strcmp( details.arg1, "d16" ) == 0){
            sprintf( arg1String, "%#04x", MMU_readWord( addr ) );
            addr = addr + 2;
        } else if( strcmp( details.arg1, "(HL)" ) == 0 || strcmp( details.arg1, "(HL+)" ) == 0 || strcmp( details.arg1, "(HL-)" ) == 0 ){
            sprintf( arg1String, "(HL)%#04x", MMU_readByte( cpuRegisters.hl ) );
        } else if ( strcmp( details.arg1, "a16" ) == 0 ){
            sprintf( arg1String, "%#06x", MMU_readWord( addr ) );
            addr = addr + 1;
        } else {
            sprintf( arg1String, "%s", details.arg1 );
        }
    }
    if( strcmp( details.arg2, "" ) != 0){
        if( strcmp( details.arg2, "(a16)" ) == 0 ){
            sprintf( arg2String, "(%#06x)", MMU_readWord( addr ) );
        } else if( strcmp( details.arg2, "d8" ) == 0){
            sprintf( arg2String, "%#04x", MMU_readByte( addr ) );
        } else if( strcmp( details.arg2, "(a8)" ) == 0 ){
            sprintf( arg2String, "(%#06x)%#04x", 0xff00|MMU_readByte( addr ), MMU_readByte( 0xff00|MMU_readByte( addr ) ) );
        } else if( strcmp( details.arg2, "(HL)" ) == 0 || strcmp( details.arg2, "(HL+)" ) == 0 || strcmp( details.arg2, "(HL-)" ) == 0 ){
            sprintf( arg2String, "(HL)%#04x", MMU_readByte( cpuRegisters.hl ) );
        } else {
            sprintf( arg2String, "%s", details.arg2 );
        }
    }
    sprintf( buff, "[0x%02x]%s %s %s", details.codePoint, details.mnemonic, arg1String, arg2String );
    return buff;
}
