#include "SpriteComponent.h"

SpriteComponent::SpriteComponent()
{
	m_x = 50;
	m_y = 50;
	m_width = 50;
	m_height = 50;
	loadedSurface = NULL;
	m_texture = NULL;
	xOffset = 0;
	timer = 0;
	m_animed = false;
}

void SpriteComponent::resetSprite()
{
	m_x = 50;
	m_y = 50;
	m_width = 50;
	m_height = 50;
	loadedSurface = NULL;
	m_texture = NULL;
	xOffset = 0;
	timer = 0;
	m_animed = false;
}

void SpriteComponent::setPathAndScreen(std::string path, SDL_Renderer* t_screen, bool t_anime)
{
	loadedSurface = SDL_LoadBMP(path.c_str());
	m_screen = t_screen;
	m_animed = t_anime;
}

void SpriteComponent::setPosAndSize(int x, int y, int width, int height)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
}

void SpriteComponent::init()
{
}

void SpriteComponent::update()
{
	timer++;
}

void SpriteComponent::render()
{
	SDL_Rect dstrect = { m_x, m_y, m_width, m_height };
	if (m_animed && timer > 10)
	{
		timer = 0;
		xOffset += 50;
		if (xOffset == 550)//to be changed for actually spritesheet
		{
			xOffset = 0;
		}
	}
	SDL_Rect srcrect = { xOffset, 0, 50, 50 };
	if (m_texture == NULL)
	{
		m_texture = SDL_CreateTextureFromSurface(m_screen, loadedSurface);
	}
	SDL_RenderCopy(m_screen, m_texture, &srcrect, &dstrect);
}