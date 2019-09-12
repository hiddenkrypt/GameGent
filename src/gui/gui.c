#include <SDL.h>
#include <stdio.h>
#include "window.h"
#include "tilemap.h"
#include "gamegent_state.h"
#include "menus.h"
#include "gui.h"

const int LCD_WIDTH = 160;
const int LCD_HEIGHT = 144;

SDL_Renderer* Gui_init () {
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL init video failed: %s\n", SDL_GetError() );
		return NULL;
	}
    if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "0" ) ) {
        printf( "Failed to set render scale quality." );
    }
    SDL_Renderer* renderer = Window_init();
    if ( SDL_RenderSetLogicalSize(renderer, LCD_WIDTH, LCD_HEIGHT) != 0 ) {
        printf( "Renderer logical size not set. SDL Error: %s\n", SDL_GetError() );
        return NULL;
    }
    if ( SDL_SetRenderDrawBlendMode( renderer, SDL_BLENDMODE_BLEND != 0 ) ) {
        printf( "Warning, blendmode failed to set." );
    }
    tiles_init( renderer );
    return renderer;
}


void Gui_draw ( SDL_Renderer*  rend, gamegent_state state ) {
    SDL_Rect LCDRect = { 0, 0, 160, 144 };
    SDL_SetRenderDrawColor( rend, 0x00, 0x81, 0x41, 0xef );
    SDL_RenderFillRect( rend, &LCDRect );
    Menus_draw( rend, state );
}


void Gui_shutdown () {
    Window_shutdown();
	SDL_Quit();
}

void Gui_handleEvent( SDL_Event e ){


}
