#include "keyBinds.h"
#include "keyCommands.h"
#include "settings.h"
#include <stdlib.h>
#include <stdio.h>

static keyBind* keyBindCollection;
static int keyBindCount = 0;


static const int DEFAULT_BIND_COUNT = 9;// always update to size of defaultKeyBinds array
static const keyBind defaultKeyBinds[] = {
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
    if(false){ // config file found keybinds
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
            break;
        }
    }
    return NO_COMMAND;
}

void KeyBinds_shutdown(){
    free( keyBindCollection );
    printf( "Keybinds shutdown." );
}
