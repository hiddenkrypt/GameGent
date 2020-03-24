#pragma once

#include <stdbool.h>

void DMG_init();
void DMG_LoadRom(char const * path);
void DMG_startEmulation();
void DMG_haltEmulation();
bool DMG_isEmulating();
bool DMG_tick();
