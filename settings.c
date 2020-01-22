#include "settings.h"
#include <stdbool.h>
#include <stdint.h>


static char* bootRomPath;
static bool runBootRom;

void Settings_init(){
    //set defaults on init

    runBootRom = true;
    bootRomPath = "DMG_ROM.bin";
}

bool Settings_get_runBootRom(){
    return runBootRom;
}
char* Settings_get_bootRomPath(){
    return bootRomPath;
}
