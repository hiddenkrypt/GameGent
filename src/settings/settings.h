#pragma once

#include <stdbool.h>
#include <SDL.h>
#include "gui/menus/recentRomStruct.h"

bool Settings_getDebugFlag();


void Settings_init();
bool Settings_get_runBootRom();
char *Settings_get_bootRomPath();

bool Settings_getRunLastRomOnBoot();
char *Settings_getLastRomPath();

recentRomList Settings_get_recentRoms();
