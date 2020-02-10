#include "SpriteComponent.h"

SpriteComponent::SpriteComponent()
{
	m_x = 50;
	m_y = 50;
	m_width = 50;
	m_height = 50;
	loadedSurface = NULL;
	m_texture = NULL;
}

//void SpriteComponent::setPath(std::string path)
//{
//	loadedSurface = SDL_LoadBMP(path.c_str());
//}

void SpriteComponent::setPathAndScreen(std::string path, SDL_Renderer* t_screen)
{
	loadedSurface = SDL_LoadBMP(path.c_str());
	m_screen = t_screen;
}

void SpriteComponent::setPosAndSize(int x, int y, int width, int height)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
}

//void SpriteComponent::render(SDL_Renderer* t_screen)
//{
//	SDL_Rect dstrect = { m_x, m_y, m_width, m_height };
//	if (m_texture == NULL)
//	{
//		m_texture = SDL_CreateTextureFromSurface(t_screen, loadedSurface);
//	}
//	SDL_RenderCopy(t_screen, m_texture, NULL, &dstrect);
//}

void SpriteComponent::init()
{
}

void SpriteComponent::update()
{
}

void SpriteComponent::render()
{
	SDL_Rect dstrect = { m_x, m_y, m_width, m_height };
	if (m_texture == NULL)
	{
		m_texture = SDL_CreateTextureFromSurface(m_screen, loadedSurface);
	}
	SDL_RenderCopy(m_screen, m_texture, NULL, &dstrect);
}
