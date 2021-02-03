#pragma once

#include <stdbool.h>

/** \brief the current state of the dmg emulation is saved as an enum
 *  the core state is used as a very simple state machine, and these are the three states.
 */
typedef enum dmgCoreStateEnum{
	STOPPED, 	/**> No rom loaded, undefined ram and register state **/
	PAUSED, 	/**> Rom loaded, but no execution on dmg ticks**/
	RUNNING		/**> Rom loaded, code executing on ticks **/
} dmgCoreState;

void DMG_init();
void DMG_loadRom(const char *path);
void DMG_startEmulation();
void DMG_haltEmulation();
void DMG_stopEmulation();
bool DMG_isEmulating();
bool DMG_tick();
dmgCoreState DMG_getCoreState();

