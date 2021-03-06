#include <string.h>
#include "cartridge.h"
#include "mmu.h"

uint8_t ram[0xffff];


/** \brief sets up the memory module, initializing the DMG ram
 *  \todo optional alternative ram setups, including random values?
 *
 */
void MMU_init(){
	for(int i = 0; i < 0xffff; i++){
		ram[i] = 0;
	}
}
char *MMU_loadRom( const char *romPath ){
	return Cartridge_load( romPath );
}
/** \brief read a byte from DMG ram
 * returns the 8 bit value stored at the given address. Address is a uint16_t so it literally can't be out of bounds.
 *
 * \param address location in ram selected for reading
 * \return value of the byte in ram at address
 */
uint8_t MMU_readByte( uint16_t address ){
	if( address > 0x0000 && address < 0x4000 ){

	}
	return ram[address];
}

/** \brief load a byte into DMG ram
 * sets the 8 bit value stored at the given address to the data provided. Address is a uint16_t so it literally can't be out of bounds.
 *
 * \param address location in ram selected for writing
 * \param data 8 bit value to set into the memory cell
 */
void MMU_writeByte( uint16_t address, uint8_t data ){
	ram[address] = data;
}

/** \brief load an array of bytes into DMG ram
 * Copies the values from a given array into the DMG ram, starting at the given address. Makes no change if the values are out of range.
 *
 * \param startAddress First location in ram selected for writing
 * \param countBytes number of values in the array to write into DMG ram
 * \param array of data 8 bit value to set into the memory cells
 * \return bool true if write is successful, false if not.
 */
bool MMU_loadRange( uint16_t startAddress, uint16_t countBytes, uint8_t *data ){
	if( ( (uint32_t)startAddress + (uint32_t)countBytes ) > 0xffff ) {
		return false;
	}
	memcpy(ram+startAddress, data, countBytes);
	printf( "Loaded %#06x bytes into memory", countBytes );
	getchar();
	return true;
}

uint16_t MMU_readWord( uint16_t address ){
	return ram[address+1] << 8 | ram[address];
}
void MMU_writeWord( uint16_t address, uint16_t data ){
	ram[address] = (uint8_t) ( data >> 8 );
	ram[address + 1] = (uint8_t) ( data | 0x0f );
}
