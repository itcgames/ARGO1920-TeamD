#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Component.h"
class SpriteComponent //: public Component
{
public:
	SpriteComponent();
	void setPath(std::string path);
	void setSize(int width, int height);
	void render(int x, int y, SDL_Renderer* t_screen);
private:
	SDL_Surface* loadedSurface;
	SDL_Texture* m_texture;
	int m_width;
	int m_height;
};