#pragma once
/**@todo: nuke this thing from orbit, break it off into various places, get it out of the project root, something!*/
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
} keyBindings;
/** \brief monolithic program state variable
 *
 * Everything about what's going on in the program right now, from settings to graphics options and more, anything that might need to be shared between systems
 * \note Always be aware of what might not need to be in here, and consider passing constituent values instead when possible. Pass this struct by value, and create functions for and modules to modify it's values after initialization.
 *
 */
typedef struct {
    bool emulating;
    bool inMenu;
    int FPS;
    bool quit;
    SDL_Renderer* renderer;
    struct {
        struct {
            bool forceIntegerScale;
        } graphics;
        keyBindings keyBinds;
    } settings;
} GameGentState;

