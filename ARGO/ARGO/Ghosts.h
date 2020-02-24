#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
class Ghost
{
public:
	Ghost();
	void setUp(SDL_Renderer* t_screen);
	int update(std::string t_pos, int t_mainPlayerNum);
	void render();
	const static int MAX_GHOSTS = 10;
private:
	SDL_Renderer* m_screen;
	SDL_Surface* m_loadedSurface;
	SDL_Texture* m_texture;
	SDL_Rect dstrect[MAX_GHOSTS];
	SDL_Rect srcrect[MAX_GHOSTS];
};