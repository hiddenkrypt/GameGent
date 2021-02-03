#pragma once


void Window_init();
void Window_shutdown();
SDL_Renderer *Window_getNewRenderer();
void Window_handleEvent(const SDL_Event * event);
