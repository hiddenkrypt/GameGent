#pragma once

#include <stdbool.h>
#include <SDL.h>

/**
 * \brief current state of the overall program
 *
 * a selection of states the overall program can be in. Different subsystems may change the program state
 */
typedef enum {
    state_main_menu /**< Program is currently in the main menu. Emulation is paused. (starting condition)*/
    //state_emulating /**< Menu is hidden, emulation is proceeding */
} gamegent_state;

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
    gamegent_state currentState;
    int FPS;
    bool quit;
    SDL_Renderer* renderer;
    struct {
        struct {
            bool FORCE_INTEGER_SCALE;
        } graphics;
        keyBindings keybinds;
    } settings;
} GameGent_State;

