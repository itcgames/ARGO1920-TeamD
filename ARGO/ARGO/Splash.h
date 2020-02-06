#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
class Splash
{
public:
	void handleEvents(SDL_Event& t_event);
	void update();
	void render(SDL_Renderer* t_renderer);
	void clean(SDL_Renderer& t_renderer, SDL_Window& t_window);
};