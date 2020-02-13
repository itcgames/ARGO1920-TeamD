#include "SpriteComponent.h"

SpriteComponent::SpriteComponent()
{
	m_x = 120;
	m_y = 120;
	m_width = 120;
	m_height = 120;
	xOffset = 0;
	timer = 0;
	m_animed = false;
	m_currentTex = 0;
}

void SpriteComponent::resetSprite()
{
	m_x = 120;
	m_y = 120;
	m_width = 120;
	m_height = 120;
	m_animed = false;
}

void SpriteComponent::setPathAndScreen(std::string path, SDL_Renderer* t_screen, bool t_anime)
{
	bool newString = true;
	m_currentTex = -1;
	for (auto currentPath : m_paths)
	{
		if (currentPath == path)
		{
			newString = false;
		}
		m_currentTex++;
	}
	if (newString)
	{
		m_paths.push_back(path);
		m_currentTex++;
	}
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
		xOffset += 120;
		if (xOffset == 600)//to be changed for actually spritesheet
		{
			xOffset = 0;
		}
	}
	SDL_Rect srcrect = { xOffset, 0, 120, 120 };

	while (loadedSurface.size() < m_paths.size())
	{
		SDL_Surface* newSurface = SDL_LoadBMP(m_paths.at(m_currentTex).c_str());
		loadedSurface.push_back(newSurface);
		m_texture.push_back(SDL_CreateTextureFromSurface(m_screen, loadedSurface.at(m_texture.size())));
		if (m_currentTex == 1)
		{
			int t = 0;
		}
	}
	SDL_RenderCopy(m_screen, m_texture.at(m_currentTex), &srcrect, &dstrect);
}