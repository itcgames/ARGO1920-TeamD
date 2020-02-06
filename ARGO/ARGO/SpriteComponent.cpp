#include "SpriteComponent.h"

SpriteComponent::SpriteComponent()
{
	this->m_width = 300;
	this->m_height = 200;
	this->loadedSurface = NULL;
	this->m_texture = NULL;
}

void SpriteComponent::setPath(std::string path)
{
	this->loadedSurface = SDL_LoadBMP(path.c_str());
}

void SpriteComponent::setSize(int width, int height)
{
	this->m_width = width;
	this->m_height = height;
}

void SpriteComponent::render(int x, int y, SDL_Renderer* t_screen)
{
	SDL_Rect dstrect = { x,y, m_width, m_height };
	this->m_texture = SDL_CreateTextureFromSurface(t_screen, this->loadedSurface);
	SDL_RenderCopy(t_screen, this->m_texture, NULL, &dstrect);
}
