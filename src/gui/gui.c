#include <SDL.h>
#include <stdio.h>
#include "../../settings.h"
#include "../../GameGent.h"
#include "window.h"
#include "tilemap.h"
#include "menuManager.h"
#include "keyCommands.h"
#include "keyBinds.h"
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
    KeyBinds_shutdown();
    Window_shutdown();
	SDL_Quit();
}

/*!
 * @brief interprets SDL events and delegates response
 * takes an SDL even from the main GameGent loop and tries to figure out what to do with it,
 * passing the interpretation to an appropriate subsystem. Currently woefully unfinished.
 * @todo handle gamestate and delegate input response to the dmg core or menu system as needed
 * @param event : SDL event to handle
 */
void GUI_handleEvent( SDL_Event event ){
    if ( event.type == SDL_KEYDOWN ){
        keyCommand command = KeyBinds_parseKeyEvent( event );
        if( command == UP ){
            MenuManager_decrementMenuIndex();
        }
        if( command == DOWN ){
            MenuManager_incrementMenuIndex();
        }
        if( command == A ){
            MenuManager_activateCurrentMenuItem();
        }
    } else if( event.type == SDL_WINDOWEVENT ){
        Window_handleEvent(&event);
    }

}


