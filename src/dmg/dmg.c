
#include <stdbool.h>
#include "cpu.h"
#include "mmu.h"
#include "dmg.h"

static bool emulating = false;

/** \brief startup emulation core
 * initializes DMG sub components and prepares emulation
 */
void DMG_init(){
    MMU_init();
    CPU_init();
}

/** \brief loads a game cartridge into the DMG
 * fetches rom information, parses rom metadata, and configures DMG appropriately.
 * \param path filepath to find the game rom.
 */
void DMG_LoadRom(char* path){

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
    if (!emulating){ return false; }
    CPU_tick();
    return true;
}

/** sets emulating to true, causing the DMG to emulate a processor clock cycle when given program control in DMG_tick() */
void DMG_startEmulation(){
    emulating = true;
}
/** sets emulating to false, causing the DMG to do nothing when given program control in DMG_tick() */
void DMG_haltEmulation(){
    emulating = false;
}
/** \brief returns state of the emulating variable \return boolean value: emulating */
bool DMG_isEmulating(){
    return emulating;
}
