
#pragma once

SDL_Renderer* GUI_init();
void GUI_draw (GameGentState GameGent) ;
void GUI_shutdown();
void GUI_handleEvent( SDL_Event e, keyBindings keybinds );
