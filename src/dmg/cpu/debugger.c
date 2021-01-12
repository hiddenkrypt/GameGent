#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "../../GameGent.h"
#include "../mmu/mmu.h"
#include "registers.h"
#include "cpu.h"
#include "codeTables.h"
#include "debugger.h"

static void stringifyInstruction( char* instructionStringBuffer, uint16_t addr, instruction details );
static void printPrompt();
static void printStatus();
static void memDump( uint16_t addr );
static void handleInput( char input );
static void pushBreakpoint(uint16_t breakpoint);
static void spliceBreakpoint( uint16_t breakpoint, uint16_t replace);

uint16_t breakpoints[20];
static uint16_t memoryDumpIndex = 0;
bool alwaysBreak = false;

void Debugger_init(){
    for(int i = 0; i < 20 ; i++){
        breakpoints[i] = 0;
    }
    pushBreakpoint( 0x206 );
    pushBreakpoint( 0x20b );
}
void Debugger_break(){
    printStatus();
    printPrompt();
    char input = getch();
	handleInput( input );
	if( memoryDumpIndex == 0 ){
        memoryDumpIndex = cpuRegisters.pc;
	}
}
bool Debugger_checkBreakpoint( uint16_t addr ){
    if( alwaysBreak ){
        return alwaysBreak;
    }
    if( addr == 0 ){
        return false;
    }
    for(int i = 0; i < 20 ; i++){
        if( breakpoints[i] == addr ){
            return true;
        }
    }
    return false;
}

static void pushBreakpoint( uint16_t breakpoint ){
    for(int i = 20; i > 0 ; i--){
        breakpoints[i] = breakpoints[i-1];
    }
    breakpoints[0] = breakpoint;
}
static void spliceBreakpoint( uint16_t breakpoint, uint16_t replace){
    for(int i = 0; i < 20 ; i++){
        if(breakpoints[i] == breakpoint){
            breakpoints[i] = replace;
            return;
        }
    }
}
static uint16_t nextBreakpoint(){
    for(int i = 20; i < 0 ; i--){
        if(breakpoints[i] >= cpuRegisters.pc){
            return breakpoints[i];
        }
    }
    return 0;
}
static void printPrompt(){
    printf("What do? \n");
    printf("[m]memdump at pc  [<] memdump -5 [>] memdump +5 [?] memdump at position\n");
    printf("[q] step forward [w] run to next break [k] kill program\n");
}

static void handleInput( char input ){
    switch( input ){
        case 'm': case 'M':
            memDump( cpuRegisters.pc );
            break;
        case '<':
            memoryDumpIndex = memoryDumpIndex - 5;
            memDump( memoryDumpIndex );
            break;
        case '>':
            memoryDumpIndex = memoryDumpIndex + 5;
            memDump( memoryDumpIndex );
            break;
        case '?':
            printf("Memdump at what address?\n");
            int in;
            scanf ("%x",&in);
            in = in % 0xffff;
            memoryDumpIndex = in;
            memDump( in );
            break;
        case 'q': case 'Q':
            printf("step: %#06x\n", cpuRegisters.pc);
            alwaysBreak = true;
            spliceBreakpoint( cpuRegisters.pc, 0 );
            break;
        case 'w': case 'W':
            spliceBreakpoint( cpuRegisters.pc, 0 );
            printf("run to next breakpoint: %#06x\n", nextBreakpoint());
            alwaysBreak = false;
            break;
        case 'k': case 'K':
            GameGent_shutdown();
            break;
        case '\0':
            break;
        default:
            printf("\n\nbad input\n\n");
    }
}
static void printStatus(){
    #ifdef _WIN32
        system("cls");
    #else
        system ("clear");
    #endif
    char zeroFlag = ' ';
    char carryFlag = ' ';
    char subFlag = ' ';
    char halfCarryFlag = ' ';
    if( CPU_getZeroFlag() ){
        zeroFlag = 'Z';
    }
    if( CPU_getCarryFlag() ){
        carryFlag = 'C';
    }
    if( CPU_getSubtractFlag() ){
        subFlag = 'N';
    }
    if( CPU_getHalfCarryFlag() ){
        halfCarryFlag = 'H';
    }
    printf( "\n   =======BREAK=======\n" );
	printf( "   ------------------------\n" );
	printf( " AF| %#06x | PC| %#06x |\n", cpuRegisters.af, cpuRegisters.pc  );
	printf( " BC| %#06x | SP| %#06x |\n", cpuRegisters.bc, cpuRegisters.sp  );
	printf( " DE| %#06x | %c %c |\n", cpuRegisters.de, zeroFlag, subFlag );
	printf( " HL| %#06x | %c %c |\n", cpuRegisters.hl, carryFlag, halfCarryFlag );
	printf( "   ------------------------\n");
	printf( " Code: \n");
    uint16_t workAddress = cpuRegisters.pc;
    for( int i = 0 ; i<6; i++ ){
        instruction currentInstruction = codeTable[ MMU_readByte( workAddress ) ];
        if( currentInstruction.codePoint == 0xCB ){
            workAddress = workAddress + 1;
            currentInstruction = prefixCodeTable[ MMU_readByte( workAddress ) ];
        }
        char* instructionString = (char*) malloc( 30 * sizeof(char) );
        stringifyInstruction( instructionString, workAddress + 1, currentInstruction );
        printf( "%#06x %s\n", workAddress, instructionString );
        free( instructionString );
        workAddress = workAddress + currentInstruction.length;
    }
}
static void stringifyInstruction( char* instructionStringBuffer, uint16_t addr, instruction details ){
    if( addr == 0x00){
        printf("stop");
    }

    char* arg1String = (char*) malloc( 10 * sizeof(char) );
    char* arg2String = (char*) malloc( 14 * sizeof(char) );
    instructionStringBuffer[0] = '\0';
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
            sprintf( arg2String, "(%#06x)%#06x", MMU_readWord( addr ), MMU_readWord( MMU_readWord( addr ) ) );
        } else if( strcmp( details.arg2, "a16" ) == 0 ){
            sprintf( arg2String, "(%#06x)", MMU_readWord( addr ) );
        } else if( strcmp( details.arg2, "d8" ) == 0 ){
            sprintf( arg2String, "%#04x", MMU_readByte( addr ) );
        } else if( strcmp( details.arg2, "r8" ) == 0 ){
            int8_t relativeAddressValue= (int8_t)MMU_readByte( addr );
            sprintf( arg2String, "%+d", relativeAddressValue );
        } else if( strcmp( details.arg2, "d16" ) == 0 ){
            sprintf( arg2String, "%#04x", MMU_readWord( addr ) );
        } else if( strcmp( details.arg2, "(a8)" ) == 0 ){
            sprintf( arg2String, "(%#06x)%#04x", 0xff00|MMU_readByte( addr ), MMU_readByte( 0xff00|MMU_readByte( addr ) ) );
        } else if( strcmp( details.arg2, "(HL)"  ) == 0 || strcmp( details.arg2, "(HL+)" ) == 0 || strcmp( details.arg2, "(HL-)" ) == 0 ){
            sprintf( arg2String, "%s%#04x", details.arg2, MMU_readByte( cpuRegisters.hl ) );
        } else {
            sprintf( arg2String, "%s", details.arg2 );
        }
    }
    sprintf( instructionStringBuffer, "[0x%02x]%s %s %s", details.codePoint, details.mnemonic, arg1String, arg2String );
    free( arg1String );
    free( arg2String );
}
static void memDump( uint16_t addr ){
    printf("raw memdump centered on %#06x\n", addr);
    for( int i = -5 ; i<6; i++ ){
        printf( "[%#06x] %#04x \n", (addr+i)%0xffff, MMU_readByte( addr+i ) );
    }
}
