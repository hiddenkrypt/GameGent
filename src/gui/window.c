
#include <SDL.h>
#include <stdio.h>
#include "window.h"

SDL_Window* mainWindow = NULL;
SDL_Renderer* mainRenderer = NULL;

const int LCD_WIDTH = 160;
const int LCD_HEIGHT = 144;
int screenWidth = 160*2;
int screenHeight = 144*2;


SDL_Renderer* Window_init(){
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL init video failed: %s\n", SDL_GetError() );
		return NULL;
	}
    if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "0" ) ) {
        printf( "Failed to set render scale quality." );
    }
    mainWindow = SDL_CreateWindow( "GameGent", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE  );
    if ( mainWindow == NULL ) {
        printf( "Window could not be created. SDL Error: %s\n", SDL_GetError() );
        return NULL;
    }
    mainRenderer = SDL_CreateRenderer( mainWindow, -1, SDL_RENDERER_ACCELERATED );
    if ( mainRenderer == NULL ) {
        printf( "Renderer could not be created. SDL Error: %s\n", SDL_GetError() );
        return NULL;
    }
    if ( SDL_RenderSetLogicalSize(mainRenderer, LCD_WIDTH, LCD_HEIGHT) != 0 ) {
        printf( "Renderer logical size not set. SDL Error: %s\n", SDL_GetError() );
        return NULL;
    }
    if ( SDL_SetRenderDrawBlendMode( mainRenderer, SDL_BLENDMODE_BLEND != 0 ) ) {
        printf( "Warning, blendmode failed to set." );
    }
	return mainRenderer;
}
void Window_shutdown(){
	SDL_DestroyWindow( mainWindow );
	SDL_DestroyRenderer( mainRenderer );
	SDL_Quit();
}
