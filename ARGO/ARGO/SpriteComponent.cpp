#include "SpriteComponent.h"

SpriteComponent::SpriteComponent()
{
	m_width = 50;
	m_height = 50;
	loadedSurface = NULL;
	m_texture = NULL;
}

void SpriteComponent::setPath(std::string path)
{
	loadedSurface = SDL_LoadBMP(path.c_str());
}

void SpriteComponent::setSize(int width, int height)
{
	m_width = width;
	m_height = height;
}

void SpriteComponent::render(int x, int y, SDL_Renderer* t_screen)
{
	SDL_Rect dstrect = { x,y, m_width, m_height };
	m_texture = SDL_CreateTextureFromSurface(t_screen, loadedSurface);
	SDL_RenderCopy(t_screen, m_texture, NULL, &dstrect);
}
