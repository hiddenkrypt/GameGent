#pragma once
#include <SDL.h>
#include "keyCommands.h"

/** \brief a connection between a keyboard command and a internal intent command */
typedef struct _keyBind{
	SDL_Keycode key;	/**< the SDL key press to look for*/
	keyCommand command; /**< the GameGent intent to interpret the key as*/
} keyBind;

void KeyBinds_init();
void KeyBinds_shutdown();
void KeyBinds_addKeyBind( keyCommand command, SDL_KeyCode key );
void KeyBinds_addKeyBindFromStrings( char *commandString, const char *keyString );
keyCommand KeyBinds_parseKeyEvent( SDL_Event event );
