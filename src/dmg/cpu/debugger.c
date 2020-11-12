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

static char* stringifyInstruction( uint16_t addr, instruction details );
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
    pushBreakpoint( 0x100 );
    pushBreakpoint( 0x200 );
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
static void printPrompt(){
    printf("What do? \n");
    printf("[m]memdump at pc  [<] memdump -5 [>] memdump +5 [?] memdump at position\n");
    printf("[q] step forward [w] run to next break [k] kill program");
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
            printf("Memdump at what address?");
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
            printf("run to next breakpoint: %#06x\n", cpuRegisters.pc);
            spliceBreakpoint( cpuRegisters.pc, 0 );
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
    printf( "\n   =======BREAK=======\n" );
	printf( "   ------------------------\n" );
	printf( " AF| %#06x |  BC| %#06x |\n", cpuRegisters.af, cpuRegisters.bc );
	printf( " DE| %#06x |  HL| %#06x |\n", cpuRegisters.de, cpuRegisters.hl );
	printf( " PC| %#06x |  SP| %#06x |\n", cpuRegisters.pc, cpuRegisters.sp );
	printf( "   ------------------------\n");
	printf( " Code: \n");
    uint16_t workAddress = cpuRegisters.pc;
    for( int i = 0 ; i<6; i++ ){
        instruction currentInstruction = codeTable[ MMU_readByte( workAddress ) ];
        if( currentInstruction.codePoint == 0xCB ){
            workAddress = workAddress + 1;
            currentInstruction = prefixCodeTable[ MMU_readByte( workAddress ) ];
        }
        char* instructionString = stringifyInstruction( workAddress + 1, currentInstruction );
        printf( "%#06x %s\n", workAddress, instructionString );
        workAddress = workAddress + currentInstruction.length;
    }
}
static char* stringifyInstruction( uint16_t addr, instruction details ){
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
        } else if( strcmp( details.arg2, "(HL)" ) == 0 || strcmp( details.arg2, "(HL+)" ) == 0 || strcmp( details.arg2, "(HL-)" ) == 0 ){
            sprintf( arg2String, "(HL)%#04x", MMU_readByte( cpuRegisters.hl ) );
        } else {
            sprintf( arg2String, "%s", details.arg2 );
        }
    }
    sprintf( buff, "[0x%02x]%s %s %s", details.codePoint, details.mnemonic, arg1String, arg2String );
    return buff;
}
static void memDump( uint16_t addr ){
    printf("raw memdump centered on %#06x\n", addr);
    for( int i = -5 ; i<6; i++ ){
        printf( "[%#06x] %#04x \n", (addr+i)%0xffff, MMU_readByte( addr+i ) );
    }
}
