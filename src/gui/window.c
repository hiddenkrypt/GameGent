
#include <SDL.h>
#include <stdio.h>
#include "window.h"

SDL_Window* mainWindow = NULL;
SDL_Renderer* mainRenderer = NULL;


int windowWidth = 160*3;
int windowHeight = 144*3;


SDL_Renderer* Window_init(){
    mainWindow = SDL_CreateWindow( "GameGent", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE  );
    if ( mainWindow == NULL ) {
        printf( "Window could not be created. SDL Error: %s\n", SDL_GetError() );
        return NULL;
    }
    mainRenderer = SDL_CreateRenderer( mainWindow, -1, SDL_RENDERER_ACCELERATED );
    if ( mainRenderer == NULL ) {
        printf( "Renderer could not be created. SDL Error: %s\n", SDL_GetError() );
        return NULL;
    }
	return mainRenderer;
}
void Window_shutdown(){
	SDL_DestroyWindow( mainWindow );
	SDL_DestroyRenderer( mainRenderer );
}
