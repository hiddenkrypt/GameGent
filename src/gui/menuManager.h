#pragma once

#include "menus/menu.h"

void MenuManager_draw(SDL_Renderer*  renderer);
void MenuManager_init();
void MenuManager_incrementMenuIndex();
void MenuManager_decrementMenuIndex();
void MenuManager_activateCurrentMenuItem();
void MenuManager_setMenu(menu newMenu);
