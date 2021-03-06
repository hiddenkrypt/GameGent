#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "keyCommands.h"
#include "keyBinds.h"

keyBind* keyBindCollection;
int keyBindCount = 0;
const int DEFAULT_BIND_COUNT = 9;// always update to size of defaultKeyBinds array
const keyBind defaultKeyBinds[] = {
	{SDLK_x, A},
	{SDLK_z, B},
	{SDLK_UP, UP},
	{SDLK_DOWN, DOWN},
	{SDLK_LEFT, LEFT},
	{SDLK_RIGHT, RIGHT},
	{SDLK_LCTRL, SELECT},
	{SDLK_LSHIFT, START},
	{SDLK_ESCAPE, MENU}
};

/** \brief sets up the keybindings that are active when the program starts
 *
 *  @todo check the config file for custom keybinds to load, fall back on defaults if none found.
 *  loads keybindsings from hardcoded defaults.
 */
void KeyBinds_init(){
	//set up keybind collection based on the number of keybind entries found in config file
	//if the number is 0 or there are any errors in them, fall back to the default
	if( false ){ // config file found keybinds
	} /*! @todo implement options config file for keybinds and other settings, update keybinds init */
	else{
		printf("No config keybinds found, using default keybinds.\n");
		keyBindCollection = malloc(DEFAULT_BIND_COUNT*sizeof(keyBind));
		for (int i = 0; i < DEFAULT_BIND_COUNT; i++){
			keyBindCollection[i] = defaultKeyBinds[i];
		}
		keyBindCount = DEFAULT_BIND_COUNT;
	}
}

/** \brief figures out what command a user is trying to invoke
 *  Runs a linear search of all keybindings until it finds one matching the SDL_Keycode
 *  of the given event, then returns the keyCommand enum for that keypress.
 * \param SDL_Event event : assumed to be a key event, used to find a relevant binding.
 * \return keyCommand : an enum indicating the command bound to that input (or NO_COMMAND
 * if not bound)
 */
keyCommand KeyBinds_parseKeyEvent( SDL_Event event ){
	for( int i = 0; i < keyBindCount; i++ ){
		if( keyBindCollection[i].key == event.key.keysym.sym ){
			return keyBindCollection[i].command;
		}
	}
	return NO_COMMAND;
}

/** \brief cleanup the KeyBinds module
 * frees up memory used by the keybind collection before shutdown.
 */
void KeyBinds_shutdown(){
	free( keyBindCollection );
	printf( "Keybinds shutdown." );
}
	/** @todo check to make sure all commands are bound */

void KeyBinds_addKeyBind( keyCommand command, SDL_KeyCode key ){
	for ( int i = 0; i < keyBindCount; i++ ){
		if( keyBindCollection[i].key == key ){
			keyBindCollection[i].command = command;
			return;
		}
	}
	keyBind *tempKeyBindCollection = malloc( (keyBindCount + 1 ) * sizeof( keyBind ) );
	for ( int i = 0; i < keyBindCount; i++ ){
		tempKeyBindCollection[i] = keyBindCollection[i];
	}
	keyBind newBind = { command, key };
	tempKeyBindCollection[ keyBindCount + 1 ] = newBind;
	keyBindCount++;
}

void KeyBinds_addKeyBindFromStrings( char *commandString, const char *keyString ){
	keyCommand commandToBind = NO_COMMAND;
	#define KEY_COMMAND_COUNT 10
	typedef struct _keyCommandStrings{
		keyCommand command; /**< the GameGent intent to interpret the key as*/
		char* commandString;
	} keyCommandStrings;
	keyCommandStrings keyCommandTable[KEY_COMMAND_COUNT] = {
		{A,"A"},
		{B,"B"},
		{START,"START"},
		{SELECT,"SELECT"},
		{UP,"UP"},
		{DOWN,"DOWN"},
		{LEFT,"LEFT"},
		{RIGHT,"RIGHT"},
		{MENU,"MENU"},
		{NO_COMMAND,"NO_COMMAND"}
	};
	for ( int i = 0; i < KEY_COMMAND_COUNT; i++ ){
		if( !strcmp( commandString, keyCommandTable[i].commandString ) ){
			commandToBind = keyCommandTable[i].command;
		}
	}
	SDL_KeyCode keyToBind = SDL_GetKeyFromName( keyString );
	KeyBinds_addKeyBind( commandToBind, keyToBind );
}
