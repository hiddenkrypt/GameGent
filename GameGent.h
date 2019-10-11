#pragma once
#include <stdbool.h>

void GameGent_shutdown();

typedef struct {
    bool inMenu;
    int FPS;
    bool quit;
    SDL_Renderer* renderer;
} GameGentState;
