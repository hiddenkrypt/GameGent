
#include "GameGent.h"
#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include "gui.h"
#include "window.h"
#include "GameGent.h"



/*!
 * @brief Initialize Everything!
 * Initializes the GameGent state, and calls all subsystem init functions.
 * @todo: breakout settings to be initialized in another function, with default values and file stored user options
 */
GameGentState init(){
    GameGentState GameGent;
    GameGent.quit = false;
    GameGent.FPS = 30;
    GameGent.emulating = false;
    GameGent.inMenu = false;

    GameGent.renderer = Gui_init();
    if ( GameGent.renderer == NULL ) {
        printf("Window Initialization Failure!");
        GameGent.quit = true;
    }
    keyBindings defaultBinds;
    defaultBinds.a = SDLK_x;
    defaultBinds.b = SDLK_z;
    defaultBinds.up = SDLK_UP;
    defaultBinds.down = SDLK_DOWN;
    defaultBinds.left = SDLK_LEFT;
    defaultBinds.right = SDLK_RIGHT;
    defaultBinds.start = SDLK_LCTRL;
    defaultBinds.select = SDLK_LSHIFT;
    defaultBinds.menu = SDLK_ESCAPE;
    GameGent.settings.keyBinds = defaultBinds;
    return GameGent;
}


/*!
 * @brief top level program cleanup
 *
 * Calls all subsystem cleanup/shutdown functions.
 */
void shutdown(){
    Gui_shutdown();
};

/*!
 * @brief program entry, main loop
 *
 * Main is the program entry point. It calls all the initializers, runs the core program loop, and calls all the sleanup/shutdown functions.
 */
int main ( int argn, char* args[] ) {
    GameGentState GameGent = init();
    SDL_Event e;
    while( !GameGent.quit ) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) {
                GameGent.quit = true;
            }
            Gui_handleEvent( e, GameGent.settings.keyBinds );
        }
        Gui_draw( GameGent );
    }
    shutdown();
    return 0;
}
