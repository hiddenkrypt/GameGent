#pragma once

#include <stdbool.h>
#include <SDL.h>
#include "../gui/menus/recentRomStruct.h"

bool Settings_getDebugFlag();


void Settings_init( bool loadFromFile );
bool Settings_getRunBootRom();
char *Settings_getBootRomPath();
bool Settings_getRunLastRomOnBoot();
char *Settings_getLastRomPath();
void Settings_setRunLastRomOnBoot( bool value );
void Settings_setLastRomPath( char* path );
void Settings_setDebugFlag( bool value );
void Settings_setRunBootRom( bool value );
void Settings_setBootRomPath( char *path );

recentRomList Settings_get_recentRoms();
