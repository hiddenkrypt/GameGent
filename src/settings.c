#include "settings.h"
#include <stdbool.h>
#include <stdint.h>
#include "gui/keyBinds.h"


static char* bootRomPath;
static char* currentBlargTest;
static bool runBootRom;
static bool debugFlag;
static bool runBlargTest;
static double cpuSpeedMultiplier;
/** \brief setup the settings module
 * gathers info on the saved settings of GameGent, and sets up default keybinds
 * @todo load setting from a saved file
 */
void Settings_init(){
	//set defaults on init
	debugFlag = false;
	runBootRom = false;
	runBlargTest = false;
	currentBlargTest = "tools/gb-test-roms-master/cpu_instrs/individual/01-special.gb";
	bootRomPath = "DMG_ROM.bin";
	KeyBinds_init(); //possibly pass settings config file info for saved binds?
}
bool Settings_getRunBlargTest(){
    return runBlargTest;
}
char* Settings_getCurrentBlargTest(){
    return currentBlargTest;
}
/** \brief this flag determines if various subsystems should be printing to the screen or not
 * @todo possibly add a whole dedicated debug module for debug mode, which opens a console window in release mode, etc.
 * \return true to enable print statements
 */
bool Settings_getDebugFlag(){
	return debugFlag;
}

/** \brief return if a bootrom should be used
 * @todo bootrom use should be off by default in a proper release
 * \return true to have the emulator core use the bootrom, false to skip it
 */
bool Settings_get_runBootRom(){
	return runBootRom;
}

/** \brief return the stored path to the bootrom
 * @todo make this load from file, and be user defined
 * \return path to the bootrom file
 *
 */
char* Settings_get_bootRomPath(){
	return bootRomPath;
}

/** \brief unimplemented! save the current settings to disc
 * @todo save the current settings to disc
 */
void Settings_save(){
}

/** \brief unimplemented! load the current settings from disc
 * @todo load the current settings to disc
 */
void Settings_load(){
}

/** \brief get the list of recent roms
 * return a list of recently played roms. Each recentRom item
 * in the list should have a full absolute path, and a short
 * (18 char truncate) name.
 * @todo actually load the list from the settings / config file, and not just use predefined test values
 *
 * \return a list of recentRom pairs
 *
 */
recentRomList Settings_get_recentRoms(){
	recentRomList list;
	list.number = 2;
	recentRom test = { "LoZ-LinksAwakening", "C:\\dev\\c\\GameGent\\tests\\LoZ-LinksAwakening-DE.gb" };
	list.items[0] = test;
	recentRom test2 = { "Tetris (World) (Re", "C:\\dev\\c\\GameGent\\tests\\Tetris (World) (Rev A).gb" };
	list.items[1] = test2;
	return list;
};
