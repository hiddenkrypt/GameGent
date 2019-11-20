#include <SDL.h>
#include <stdio.h>
#include "settings.h"
#include "GameGent.h"
#include "window.h"
#include "tilemap.h"
#include "menuManager.h"
#include "gui.h"

const int LCD_WIDTH = 160;
const int LCD_HEIGHT = 144;

/*!
 * @brief Intializes Gui system
 *
 * Initializes all Gui subsystems, creating an SDL window and associated renderer.
 * @todo breakout window and SDL init
 * @see Window_init()  about breaking out window and SDL init
 */
SDL_Renderer* GUI_init () {
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL init video failed: %s\n", SDL_GetError() );
		return NULL;
	}
    if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "0" ) ) {
        printf( "Failed to set render scale quality." );
    }
    Window_init();
    SDL_Renderer* mainRenderer = Window_getNewRenderer();
    if ( SDL_RenderSetLogicalSize(mainRenderer, LCD_WIDTH, LCD_HEIGHT) != 0 ) {
        printf( "Renderer logical size not set. SDL Error: %s\n", SDL_GetError() );
        return NULL;
    }
    if ( SDL_SetRenderDrawBlendMode( mainRenderer, SDL_BLENDMODE_BLEND != 0 ) ) {
        printf( "Warning, blendmode failed to set." );
    }
    Tiles_init( mainRenderer );
    MenuManager_init();
    return mainRenderer;
}

/*!
 * @brief Draws the gui
 *
 * draws the next frame of the program based on program state
 * @param gameGent the current state of the gamegent
 */
void GUI_draw ( GameGentState gameGent ) {
    SDL_SetRenderDrawColor( gameGent.renderer, 0x00, 0x00, 0x00, 0xff );
    SDL_RenderClear( gameGent.renderer );
    SDL_Rect LCDRect = { 0, 0, 160, 144 };
    SDL_SetRenderDrawColor( gameGent.renderer, 0x00, 0x81, 0x41, 0xef );
    SDL_RenderFillRect( gameGent.renderer, &LCDRect );

    MenuManager_draw( gameGent.renderer );

    SDL_Delay(1000/gameGent.FPS);
    SDL_RenderPresent( gameGent.renderer );
}

/*!
 * @brief Cleanup gui subsystems
 *
 * Calls all gui subsystem cleanup/shutdown functions.
 */
void GUI_shutdown () {
    Window_shutdown();
	SDL_Quit();
}

/*!
 * @brief Handles user input events
 *
 * @todo so many things
 * @todo create input interpreter to generify multiple types of input to virtual system inputs
 * @todo figure out a more elegant way to handle menu state
 * @param e SDL event to handle
 * \param currentState what state the program is in
 * @param keyBinds Current binding of key symbols to virtual program commands (a,b,up down left right, select, start, menu)
 */
void GUI_handleEvent( SDL_Event event ){
    if ( event.type == SDL_KEYDOWN ){
        if ( event.key.keysym.sym == Settings_defaultBinds.a ) {
            MenuManager_activateCurrentMenuItem();
            printf("a");
        } else if ( event.key.keysym.sym == Settings_defaultBinds.b ){
            printf("b");
        } else if ( event.key.keysym.sym == Settings_defaultBinds.up ){
            printf("up");
            MenuManager_decrementMenuIndex();
        } else if ( event.key.keysym.sym == Settings_defaultBinds.down ){
            printf("down");
            MenuManager_incrementMenuIndex();
        } else if ( event.key.keysym.sym == Settings_defaultBinds.left ){
            printf("left");
        } else if ( event.key.keysym.sym == Settings_defaultBinds.right ){
            printf("right");
        } else if ( event.key.keysym.sym == Settings_defaultBinds.select ){
            printf("select");
        } else if ( event.key.keysym.sym == Settings_defaultBinds.start ){
            printf("start");
        } else if ( event.key.keysym.sym == Settings_defaultBinds.menu ){
            printf("menu");
        }
        printf("\n");

    } else if( event.type == SDL_WINDOWEVENT ){
        Window_handleEvent(&event);
    }

}


