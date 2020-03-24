
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <SDL.h>

#include "tilemap.h"


const char* CHARACTER_MAP_PATH = "img/CharacterTileMap.bmp";
SDL_Texture* charMap = NULL;


bool Tiles_init( SDL_Renderer* renderer ){
	SDL_Surface* loadedSurface = SDL_LoadBMP( CHARACTER_MAP_PATH );

	if( loadedSurface == NULL ) {
		printf( "Unable to load image %s! SDL_image Error: %s\n", CHARACTER_MAP_PATH, SDL_GetError() );
		return false;
	}
	SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0xFF, 0xFF ) );
	charMap = SDL_CreateTextureFromSurface( renderer, loadedSurface );
	SDL_FreeSurface( loadedSurface );
	if( charMap == NULL ) {
		printf( "Unable to create texture from %s! SDL Error: %s\n", CHARACTER_MAP_PATH, SDL_GetError() );
		return false;
	}
	return true;
}


void Tiles_paintCharAt(int x, int y, unsigned const char character, SDL_Renderer* renderer ){
	SDL_Rect tileClip = { ((character-32)%8)*8, ((character-32)/8)*8, 8, 8 };
	SDL_Rect tilePos = {x*8, y*8, 8, 8};
	//printf ( "PAINT %d:'%c' at {%d,%d}: clip{%d,%d,%d,%d}, pos{%d,%d,%d,%d}\n\n", character,character, x, y, tileClip.x,tileClip.y,tileClip.w,tileClip.h,tilePos.x,tilePos.y,tilePos.w,tilePos.h );
	SDL_RenderCopy( renderer, charMap, &tileClip, &tilePos );
}


void Tiles_paintStringAt(int x, int y, const char* message, SDL_Renderer* renderer ){
	int msgLen = strlen(message);
	int i=0;
	for(i=0; i < msgLen; i++){
		Tiles_paintCharAt(x+i,y,message[i], renderer);
	}
}


void Tiles_cleanup(){
	SDL_DestroyTexture( charMap );
}







