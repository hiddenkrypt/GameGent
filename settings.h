#pragma once

#include <stdbool.h>
#include <SDL.h>

/** \brief a single set of program bindings
 *
 * A single set of SDL_Keycodes "mapped to various basic GameGent inputs
 */

void Settings_init();
bool Settings_get_runBootRom();
char* Settings_get_bootRomPath();


