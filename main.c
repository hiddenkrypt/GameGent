
#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include "main.h"
#include "src\gui\gui.h"
#include "src\gui\window.h"




enum program_state currentState = state_main_menu;
SDL_Renderer* rend = NULL;

int main ( int argn, char* args[] ) {
    rend = Gui_init();
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
            }
        }
        SDL_Delay(1);
        if(currentState == state_main_menu){
            Gui_draw( rend );
        }
        SDL_Rect LCDRect = { 0, 0, 160, 144 };
        SDL_SetRenderDrawColor( rend, 0x00, 0x81, 0x41, 0x00 );
        SDL_RenderFillRect( rend, &LCDRect );
        SDL_RenderPresent( rend );
    }
    shutdown();
    return 0;
}

void shutdown(){
    Gui_shutdown();
}
