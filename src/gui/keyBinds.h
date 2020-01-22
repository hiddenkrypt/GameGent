#pragma once
#include "keyCommands.h"
#include <SDL.h>

typedef struct _keyBind{
    SDL_Keycode key;
    keyCommand command;
} keyBind;

void KeyBinds_init();
void KeyBinds_shutdown();
keyCommand KeyBinds_parseKeyEvent( SDL_Event event );
