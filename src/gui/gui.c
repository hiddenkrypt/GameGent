#include <SDL.h>
#include "window.h"
#include "tilemap.h"
#include "gamegent_state.h"
#include "menus.h"
#include "gui.h"



SDL_Renderer* Gui_init () {
    SDL_Renderer* renderer = Window_init();
    tiles_init( renderer );
    return renderer;
}


void Gui_draw ( SDL_Renderer*  rend, gamegent_state state ) {
    SDL_Rect LCDRect = { 0, 0, 160, 144 };
    SDL_SetRenderDrawColor( rend, 0x00, 0x81, 0x41, 0xef );
    SDL_RenderFillRect( rend, &LCDRect );
    SDL_SetRenderDrawColor( rend, 0x00, 0x00, 0x00, 0xff );
    tiles_paintStringAt( 8, 8, "YEET", rend);
    Menus_draw( rend, state );
}


void Gui_shutdown () {
    Window_shutdown();
}

void Gui_handleEvent( SDL_Event e ){


}
