#pragma once

#include <stdbool.h>
#include <SDL.h>
#include "gui/menus/recentRomStruct.h"


void Settings_init();
bool Settings_get_runBootRom();
char* Settings_get_bootRomPath();

recentRomList Settings_get_recentRoms();
