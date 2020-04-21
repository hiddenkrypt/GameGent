
#include <stdbool.h>
#include <stdio.h>
#include "../settings.h"
#include "cpu/cpu.h"
#include "mmu/mmu.h"
#include "dmg.h"

/** @todo LCD / PPU
 * @todo APU
 * @todo serial???
 */

dmgCoreState state = STOPPED;

void loadBootRom(char* path){
	printf("loading bootrom\n");
	FILE* bootRom = fopen(path, "r");
	if( bootRom == NULL ){
		printf("Bootrom failed to open, make sure bootrom exists at %s\n", path);
		/**\todo reset registers as they should be post-bootup*/
		return;
	}
	uint8_t bootRomData[0xff];
	fread(bootRomData, 1, 0xff, bootRom);
	bool success = MMU_loadRange( 0x0000, 0xff, bootRomData );
	if( !success ){
		printf("MMU load bootrom failure.\n");
	}
	fclose( bootRom );
}


/** \brief startup emulation core
 * initializes DMG sub components and prepares emulation
 */
void DMG_init(){
	MMU_init();
	CPU_init();
	if( Settings_get_runBootRom() ){
		loadBootRom( Settings_get_bootRomPath() );
	}
	state = RUNNING;
}

/** \brief loads a game cartridge into the DMG
 * fetches rom information, parses rom metadata, and configures DMG appropriately.
 * \param path filepath to find the game rom.
 */
void DMG_LoadRom( char const * path){

}




/** \brief gives the DMG some time to execute emulation
 *
 *  passes program control to the DMG emulation as a part of the Main Program Loop
 * if emulating is FALSE, this does nothing but return.
 * \todo do anything
 * \todo add check for loaded rom
 * \todo pause for DMG clock rate management.
 * \return bool for whether the DMG is currently emulating
 */
bool DMG_tick(){
	if ( state == RUNNING ){
		CPU_tick();
		return true;
	}
	return false;
}

/** \brief shuts the emulator coredown
 *
 * changes emulator core to STOPPED. This has no effect on the CPU or MMU,
 * so those may be in an undefined state. a new rom must be loaded to get
 * the core running again, which will clear out those values.
 *
 */
void DMG_stopEmulation(){
	state = STOPPED;
}

/** \brief pauses the emulator core
 * a core pause can be resumed, and may allow for step debugging later.
 * This is called when a menu is brought up. Has no effect on a STOPPED
 * core.
 */
void DMG_pauseEmulation(){
	if( state == RUNNING ){
		state = PAUSED;
	}
}

/** \brief allows the emulator core to resume
 * If the core has been paused by a menu or user action, it can be
 * resumed. If the core is STOPPED, this has no effect.
 */
void DMG_resumeEmulation(){
	if( state == PAUSED ){
		state = RUNNING;
	}
}

/** \brief is the core is currently running something, paused or not
 * If the core has a rom loaded and has been executing it's code,
 * this returns true. The core may be paused and need resuming, but
 * it is ready at least to resume.
 *
 * \return true if the core is currently ready to continue execution, false if STOPPED.
 */
bool DMG_isEmulating(){
	return state == RUNNING || state == PAUSED;
}

/** \brief read the current core state
 * STOPPED, PAUSED, or RUNNING, this returns the current state of the core
 */
dmgCoreState DMG_getCoreState(){
	return state;
}
