#include "settings.h"
#include <stdbool.h>
#include <stdint.h>
#include "src/gui/keyBinds.h"


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
    recentRom test = {"ROMNAME","PATH"};
    list.items[0] = test;
    recentRom test2 = {"butts","PATH"};
    list.items[1] = test2;
    return list;
};
