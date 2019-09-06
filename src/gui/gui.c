#include <SDL.h>
#include "gui.h"
#include "window.h"

SDL_Renderer* Gui_init () {
    return Window_init();
}


void Gui_draw ( SDL_Renderer*  rend ) {

}


void Gui_shutdown () {
    Window_shutdown();
}
