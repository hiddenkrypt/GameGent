
#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include "main.h"
#include "src\gui\window.h"



enum program_state currentState = state_main_menu;
SDL_Renderer* rend = NULL;

int main ( int argn, char* args[] ) {

    rend = Window_init();
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
    }
    shutdown();
    return 0;
}

void shutdown(){
    Window_shutdown();
}
