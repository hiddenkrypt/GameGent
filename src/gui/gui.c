#include <SDL.h>
#include <stdio.h>
#include "GameGent.h"
#include "window.h"
#include "tilemap.h"
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


void Gui_draw ( GameGent_State GameGent ) {
    SDL_SetRenderDrawColor( GameGent.renderer, 0x00, 0x00, 0x00, 0xff );
    SDL_RenderClear( GameGent.renderer );
    SDL_Rect LCDRect = { 0, 0, 160, 144 };
    SDL_SetRenderDrawColor( GameGent.renderer, 0x00, 0x81, 0x41, 0xef );
    SDL_RenderFillRect( GameGent.renderer, &LCDRect );

    Menus_draw( GameGent.renderer, GameGent.currentState );

    SDL_Delay(1000/GameGent.FPS);
    SDL_RenderPresent( GameGent.renderer );
}


void Gui_shutdown () {
    Window_shutdown();
	SDL_Quit();
}

void Gui_handleEvent( SDL_Event e, GameGent_State GameGent ){
    if (e.type == SDL_KEYDOWN){
        printf( "Keydown- Scancode: %s,  KeyName: %s\n",
            SDL_GetScancodeName(e.key.keysym.scancode),
            SDL_GetKeyName(e.key.keysym.sym));
    }

}
