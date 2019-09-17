#pragma once
typedef struct{
    int itemCount;
    void (*activate)(int);
    void (*draw)(SDL_Renderer*, int);
} Menu;
