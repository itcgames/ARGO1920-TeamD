#include "Sprite.h"

Sprite::Sprite()
{
	m_texture = NULL;
	m_width = 300;
	m_height = 200;
}

bool Sprite::loadFromFile(const char* path, SDL_Renderer* t_screen)
{
	//loadedSurface = IMG_Load(path);
	loadedSurface = SDL_LoadBMP(path);
	m_texture = SDL_CreateTextureFromSurface(t_screen, loadedSurface);
	if (m_texture == NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Sprite::setSize(int width, int height)
{
	m_width = width;
	m_height = height;
}

void Sprite::render(int x, int y, SDL_Renderer* t_screen)
{
	SDL_Rect dstrect = { x,y, m_width, m_height };
	SDL_RenderCopy(t_screen, m_texture, NULL, &dstrect);
}
