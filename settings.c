#include "settings.h"
#include <stdbool.h>
#include <stdint.h>


static char* bootRomPath;
static bool runBootRom;
keyBindSet Settings_defaultBinds;

void Settings_init(){
    //set defaults on init

    Settings_defaultBinds.a = SDLK_x;
    Settings_defaultBinds.b = SDLK_z;
    Settings_defaultBinds.up = SDLK_UP;
    Settings_defaultBinds.down = SDLK_DOWN;
    Settings_defaultBinds.left = SDLK_LEFT;
    Settings_defaultBinds.right = SDLK_RIGHT;
    Settings_defaultBinds.start = SDLK_LCTRL;
    Settings_defaultBinds.select = SDLK_LSHIFT;
    Settings_defaultBinds.menu = SDLK_ESCAPE;

    runBootRom = true;
    bootRomPath = "DMG_ROM.bin";
}

bool Settings_get_runBootRom(){
    return runBootRom;
}
char* Settings_get_bootRomPath(){
    return bootRomPath;
}