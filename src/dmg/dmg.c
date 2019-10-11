
#include <stdbool.h>
#include <stdio.h>
#include "settings.h"
#include "cpu.h"
#include "mmu.h"
#include "dmg.h"

static bool emulating = false;

void loadBootRom(char* path){
    printf("loading bootrom\n");
    FILE* bootRom = fopen(path, "r");
    if( bootRom == NULL ){
        printf("Failed to open");
        /**\todo reset registers as they should be post-bootup*/
        return;
    }
    uint8_t bootRomData[256];
    fread(bootRomData, 1, 256, bootRom);
    for( int j = 0; j < 32; j++){
        for(int i=0; i < 8; i++){
            printf("%#04x ", bootRomData[i+(j*8)]);
        }
        printf("\n");
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

    CPU_tick();CPU_tick();//test CPU_crash
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
