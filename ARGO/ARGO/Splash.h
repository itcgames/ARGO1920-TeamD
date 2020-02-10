#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
class Splash
{
public:
	Splash();
	void handleEvents(SDL_Event& t_event);
	void update();
	void render(SDL_Renderer* t_renderer);
	void clean(SDL_Renderer& t_renderer, SDL_Window& t_window);

private:
	SDL_Surface* loadedSurface;
	SDL_Texture* m_texture;
	int m_width;
	int m_height;
	int m_x;
	int m_y;
};