#pragma once

#include <SDL.h>
#include <stdbool.h>

bool Tiles_init( SDL_Renderer *renderer );
void Tiles_paintStringAt(int x, int y, const char *message, SDL_Renderer *renderer );
void Tiles_paintCharAt(int x, int y, unsigned const char character, SDL_Renderer *renderer );
void Tiles_cleanup();
