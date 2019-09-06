#include <SDL.h>
#include "gui.h"
#include "window.h"
#include "gui_state.h"



enum gui_state currentGuiState = gui_state_main_menu;

SDL_Renderer* Gui_init () {
    return Window_init();
}


void Gui_draw ( SDL_Renderer*  rend ) {
    SDL_Rect LCDRect = { 0, 0, 160, 144 };
    SDL_SetRenderDrawColor( rend, 0x00, 0x81, 0x41, 0xef );
    SDL_RenderFillRect( rend, &LCDRect );
    if ( currentGuiState == gui_state_main_menu ){

    }
}


void Gui_shutdown () {
    Window_shutdown();
}

void Gui_handleEvent( SDL_Event e ){

}
