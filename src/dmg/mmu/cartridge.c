
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cartridgeHeaderStructure.h"
#include "cartridge.h"

uint8_t *fullRom;
long romSize;

char *Cartridge_load( const char* romPath ) {

	FILE* rom = fopen( romPath, "rb" );
	if( rom == NULL ){
		printf( "Rom failed to open, make sure rom exists at %s\n", romPath);
		return "Rom failed to open, make sure rom file exists";
	}
    if ( ferror( rom ) ){
        printf( "Unknown File Error\n" );
        return "Unknown file error";
    }
    fseek( rom, 0, SEEK_END );
    romSize = ftell( rom );
    rewind( rom );
    fullRom = malloc( romSize );
    if( fullRom == NULL ){
        printf("Rom too big for memory\n");
        return "Rom too big for memory";
    }
    int readCount = fread( fullRom, 1, romSize, rom );
    if( readCount == 0 ){
        printf("File read error\n");
        return "File read error\n";
    }
    fclose( rom );
    return "";
}
