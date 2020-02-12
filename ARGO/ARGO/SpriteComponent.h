#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Component.h"
class SpriteComponent : public Component
{
public:
	SpriteComponent();
	void resetSprite();
	void setPathAndScreen(std::string path, SDL_Renderer* t_screen, bool t_anime = false);
	void setPosAndSize(int x, int y, int width, int height);
	void init() override;
	void update() override;
	void render() override;
private:
	SDL_Surface* loadedSurface;
	SDL_Texture* m_texture;
	SDL_Renderer* m_screen;
	int m_width;
	int m_height;
	int m_x;
	int m_y;
	int xOffset;
	int timer;
	int m_animed;
};