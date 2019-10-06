#include <stdint.h>
#include "mmu.h"

static uint8_t ram[0xffff];


/** \brief sets up the memory module, initializing the DMG ram
 *  \todo optional alternative ram setups, including random values?
 *
 */
void MMU_init(){
    for(int i = 0; i < 0xFFFF; i++){
        ram[i] = 0;
    }
    ram[1] = 0x7b;
}

/** \brief read a byte from DMG ram
 * returns the 8 bit value stored at the given address. Address is a uint16_t so it literally can't be out of bounds.
 *
 * \param address location in ram selected for reading
 * \return value of the byte in ram at address
 */
uint8_t MMU_readByte( uint16_t address ){
    printf("READ; value %#x @ %#x\n", ram[address], address);
    return ram[address];
}
