
#include "GameGent.h"
#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include "gamegent_state.h"
#include "gui.h"
#include "window.h"
#include "GameGent.h"


GameGent_State GameGent;

/*!
 * @brief Intitialize Everything!
 * Initializes the GameGent state, and calls all subsystem init functions.
 */
void GameGent_Init(){
    GameGent.quit = false;
    GameGent.FPS = 2;
    GameGent.currentState = state_main_menu;

    GameGent.renderer = Gui_init();
    if ( GameGent.renderer == NULL ) {
        printf("Window Initialization Failure!");
        GameGent.quit = true;
    }
}
/*!
 * @brief top level program cleanup
 *
 * Calls all subsystem cleanup/shutdown functions.
 */
void GameGent_Shutdown(){
    Gui_shutdown();
};
/*!
 * @brief program entry, main loop
 *
 * Main is the program entry point. It calls all the initializers, runs the core program loop, and calls all the sleanup/shutdown functions.
 */
int main ( int argn, char* args[] ) {
    GameGent_Init();
    SDL_Event e;
    while( !GameGent.quit ) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) {
                GameGent.quit = true;
            }
            Gui_handleEvent( e );
            if (e.type == SDL_KEYDOWN){
                printf( "Keydown- Scancode: %s,  KeyName: %s\n",
                    SDL_GetScancodeName(e.key.keysym.scancode),
                    SDL_GetKeyName(e.key.keysym.sym));
            }
        }
        Gui_draw(GameGent);
    }
    GameGent_Shutdown();
    return 0;
}
