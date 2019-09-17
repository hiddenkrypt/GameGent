
#pragma once

SDL_Renderer* Gui_init();
void Gui_draw (GameGent_State GameGent) ;
void Gui_shutdown();
void Gui_handleEvent( SDL_Event e, keyBindings keybinds );
