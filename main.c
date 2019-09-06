
#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include "main.h"
#include "src\gui\gui.h"
#include "src\gui\window.h"


enum program_state currentState = state_menu;


int main ( int argn, char* args[] ) {
    SDL_Renderer* rend = Gui_init();
    if ( rend == NULL ) {
        printf("Window Initialization Failure!");
        return -1;
    }
    SDL_Event e;
    bool quit = false;
    while( !quit ) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) {
                quit = true;
            } else if ( currentState == state_menu ) {
                Gui_handleEvent( e );
            }
        }
        SDL_Delay(1);
        if(currentState == state_menu){
            Gui_draw( rend );
        }
        SDL_RenderPresent( rend );
    }
    shutdown();
    return 0;
}

void shutdown(){
    Gui_shutdown();
}
