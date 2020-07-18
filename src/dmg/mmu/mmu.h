#pragma once
#include <stdbool.h>
#include <stdint.h>

void MMU_init();
uint8_t MMU_readByte( uint16_t address );
void MMU_loadByte( uint16_t address, uint8_t data );
bool MMU_loadRange( uint16_t startAddress, uint16_t countBytes, uint8_t* data );
uint16_t MMU_readWord( uint16_t address );
void MMU_loadWord( uint16_t address, uint16_t data );
