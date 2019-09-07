

#include <stdbool.h>



 bool tiles_init( SDL_Renderer* renderer );

void tiles_paintStringAt(int x, int y, char* message, SDL_Renderer* renderer );
void tiles_paintCharAt(int x, int y, char character, SDL_Renderer* renderer );

void tiles_cleanup();
