#pragma once

#include <SDL.h>
#include "menus/menu.h"
#include "keyCommands.h"

void MenuManager_draw( SDL_Renderer * renderer );
void MenuManager_init();
void MenuManager_incrementMenuIndex();
void MenuManager_decrementMenuIndex();
void MenuManager_activateCurrentMenuItem();
void MenuManager_setMenu( menu newMenu );
void MenuManager_handleCommand( keyCommand command );
