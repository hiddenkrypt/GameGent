#pragma once

#include <stdbool.h>
#include <SDL.h>

#include "gamegent_state.h"

typedef struct {
    gamegent_state currentState;
    int FPS;
    bool quit;
    struct {
        struct {
            bool FORCE_INTEGER_SCALE;
        } graphics;
        struct {
            SDL_Keycode a;
            SDL_Keycode b;
            SDL_Keycode up;
            SDL_Keycode down;
            SDL_Keycode left;
            SDL_Keycode right;
            SDL_Keycode start;
            SDL_Keycode select;
            SDL_Keycode menu;
        } keybinds;
    } settings;
} GameGent_State;

extern GameGent_State GameGent;

void GameGent_Shutdown();
