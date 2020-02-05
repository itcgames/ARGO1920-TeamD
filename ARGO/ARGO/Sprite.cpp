#include "Sprite.h"

Sprite::Sprite()
{
	m_texture = NULL;
	m_width = 300;
	m_height = 200;
}

bool Sprite::loadFromFile(std::string path, SDL_Renderer* t_screen)
{
	loadedSurface = SDL_LoadBMP(path.c_str());
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

void Sprite::setRect(int x, int y, int width, int height)
{
	fullRect = { x,y,width,height };
}

void Sprite::render(int x, int y, SDL_Renderer* t_screen)
{
	SDL_Rect renderQuad = { 0, 0, 300, 200 };
	if (&fullRect != NULL)
	{
		renderQuad.w = fullRect.w;
		renderQuad.h = fullRect.h;
	}
	SDL_RenderCopy(t_screen, m_texture, NULL, &renderQuad);
}
