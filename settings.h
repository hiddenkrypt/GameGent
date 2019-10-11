#pragma once

#include <stdbool.h>
#include <SDL.h>

/** \brief a single set of program bindings
 *
 * A single set of SDL_Keycodes "mapped to various basic GameGent inputs
 */

typedef struct {
    SDL_Keycode a;
    SDL_Keycode b;
    SDL_Keycode up;
    SDL_Keycode down;
    SDL_Keycode left;
    SDL_Keycode right;
    SDL_Keycode start;
    SDL_Keycode select;
    SDL_Keycode menu;
} keyBindSet;

void Settings_init();

extern keyBindSet Settings_defaultBinds;
