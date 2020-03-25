#pragma once

#include <stdbool.h>

typedef enum dmgCoreStateEnum{
	STOPPED, 	/**> No rom loaded, undefined ram and register state **/
	PAUSED, 	/**> Rom loaded, but no execution on dmg ticks**/
	RUNNING		/**> Rom loaded, code executing on ticks **/
} dmgCoreState;

void DMG_init();
void DMG_LoadRom(char const * path);
void DMG_startEmulation();
void DMG_haltEmulation();
void DMG_stopEmulation();
bool DMG_isEmulating();
bool DMG_tick();
dmgCoreState DMG_getCoreState();

