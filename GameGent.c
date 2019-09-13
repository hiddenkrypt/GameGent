
#include "GameGent.h"
#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include "main.h"
#include "gamegent_state.h"
#include "gui.h"
#include "window.h"
#include "GameGent.h"


GameGent_State GameGent;

void GameGent_Init(){
    GameGent.quit = false;
    GameGent.FPS = 2;
    GameGent.currentState = state_main_menu;

}
/*!
 * @brief program entry, main loop
 *
 * Main is the program entry point. It calls all the initializers, runs the core program loop, and calls all the sleanup/shutdown functions.
 */
int main ( int argn, char* args[] ) {
    GameGent_Init();
    SDL_Renderer* rend = Gui_init();
    if ( rend == NULL ) {
        printf("Window Initialization Failure!");
        return -1;
    }
    SDL_Event e;
    while( !GameGent.quit ) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) {
                GameGent.quit = true;
            } else if ( GameGent.currentState == state_main_menu ) {
                Gui_handleEvent( e );
            }
            if (e.type == SDL_KEYDOWN){
                printf( "Keydown- Scancode: %s,  KeyName: %s\n", SDL_GetScancodeName(e.key.keysym.scancode),
      SDL_GetKeyName(e.key.keysym.sym));
            }
        }

        SDL_SetRenderDrawColor( rend, 0x00, 0x00, 0x00, 0xff );
        SDL_RenderClear( rend );
        SDL_Delay(1000/GameGent.FPS);
        Gui_draw( rend,  GameGent.currentState );
        SDL_RenderPresent( rend );
    }
    GameGent_Shutdown();
    return 0;
}
/*!
 * @brief top level program cleanup
 *
 * Calls all subsystem cleanup/shutdown functions.
 */
void GameGent_Shutdown(){
    Gui_shutdown();
};
