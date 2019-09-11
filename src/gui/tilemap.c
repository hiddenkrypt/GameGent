
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <SDL.h>

#include "tilemap.h"


const char* tiles_CharacterMapPath = "img/CharacterTileMap.bmp";
SDL_Texture* tiles_charMap = NULL;


bool tiles_init( SDL_Renderer* renderer ){
	SDL_Surface* loadedSurface = SDL_LoadBMP( tiles_CharacterMapPath );

	if( loadedSurface == NULL ) {
		printf( "Unable to load image %s! SDL_image Error: %s\n", tiles_CharacterMapPath, SDL_GetError() );
		return false;
	}
    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0xFF, 0xFF ) );
    tiles_charMap = SDL_CreateTextureFromSurface( renderer, loadedSurface );
    SDL_FreeSurface( loadedSurface );
    if( tiles_charMap == NULL ) {
		printf( "Unable to create texture from %s! SDL Error: %s\n", tiles_CharacterMapPath, SDL_GetError() );
		return false;
    }
    return true;
}

void tiles_paintCharAt(int x, int y, unsigned char character, SDL_Renderer* renderer ){
    SDL_Rect tileClip = { ((character-32)%8)*8, ((character-32)/8)*8, 8, 8 };
    SDL_Rect tilePos = {x*8, y*8, 8, 8};
    printf ( "PAINT %d:'%c' at {%d,%d}: clip{%d,%d,%d,%d}, pos{%d,%d,%d,%d}\n\n", character,character, x, y, tileClip.x,tileClip.y,tileClip.w,tileClip.h,tilePos.x,tilePos.y,tilePos.w,tilePos.h );
    SDL_RenderCopy( renderer, tiles_charMap, &tileClip, &tilePos );
}
void tiles_paintStringAt(int x, int y, char* message, SDL_Renderer* renderer ){
    int msgLen = strlen(message);
    int i=0;
    for(i=0; i < msgLen; i++){
        tiles_paintCharAt(x+i,y,message[i], renderer);
    }
}
void tiles_cleanup(){
	SDL_DestroyTexture( tiles_charMap );
}







