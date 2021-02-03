#pragma once

#include <SDL.h>
#include <stdbool.h>

void GameGent_shutdown();

/** \brief a struct for holding the sate of the GameGent. Maybe useless. Maybe replace this. @todo maybe replace GameGentState? */
typedef struct {
	bool inMenu;
	int FPS;
	bool quit;
	SDL_Renderer *renderer;
} GameGentState;
