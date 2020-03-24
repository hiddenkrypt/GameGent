#include "settings.h"
#include <stdbool.h>
#include <stdint.h>
#include "gui/keyBinds.h"


static char* bootRomPath;
static bool runBootRom;

void Settings_init(){
	//set defaults on init

	runBootRom = true;
	bootRomPath = "DMG_ROM.bin";
	KeyBinds_init(); //possibly pass settings config file info for saved binds?
}

bool Settings_get_runBootRom(){
	return runBootRom;
}
char* Settings_get_bootRomPath(){
	return bootRomPath;
}


void Settings_save(){
}
void Settings_load(){
}
recentRomList Settings_get_recentRoms(){
	recentRomList list;
	list.number = 2;
	recentRom test = { "LoZ-LinksAwakening", "C:\\dev\\c\\GameGent\\tests\\LoZ-LinksAwakening-DE.gb" };
	list.items[0] = test;
	recentRom test2 = { "Tetris (World) (Re", "C:\\dev\\c\\GameGent\\tests\\Tetris (World) (Rev A).gb" };
	list.items[1] = test2;
	return list;
};
