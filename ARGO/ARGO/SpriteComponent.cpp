#include "SpriteComponent.h"

SpriteComponent::SpriteComponent()
{
	m_x = 120;
	m_y = 120;
	m_width = 120;
	m_height = 120;
	xOffset = 0;
	yOffset = 0;
	timer = 0;
	m_animed = false;
	m_currentTex = 0;
	m_currentState = PlayerStates::IdlePlayer;
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
	int counter = m_currentTex;
	for (auto currentPath : m_paths)
	{
		counter++;
		if (currentPath == path)
		{
			newString = false;
			m_currentTex = counter;
		}
		
	}
	if (newString)
	{
		m_paths.push_back(path);
		counter++;
		m_currentTex = counter;
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

void SpriteComponent::updateState(PlayerStates t_newState)
{
	if (t_newState != m_currentState)
	{
		auto changeCheck = m_animeStates.getCurrent();
		switch (t_newState)
		{
		case IdlePlayer:
			m_animeStates.idle();
			break;
		case MovingPlayer:
			m_animeStates.moving();
			break;
		case PushingPlayer:
			m_animeStates.pushing();
			break;
		case DyingPlayer:
			m_animeStates.dying();
			break;
		default:
			break;
		}
		if (changeCheck != m_animeStates.getCurrent())
		{
			m_currentState = t_newState;
			xOffset = 480;
			timer = MAX_TIME;
		}

	}
}

PlayerStates SpriteComponent::getCurrentState()
{
	return m_currentState;
}

bool SpriteComponent::finishedAnime()
{
	if (timer >= MAX_TIME-1 && xOffset >= 480)
	{
		return true;
	}
	return false;
}

void SpriteComponent::init()
{
}

void SpriteComponent::update()
{
	timer++;
	if (m_animed && timer >= MAX_TIME)
	{
		timer = 0;
		xOffset += 120;
		if (xOffset == 600)//to be changed for actually spritesheet
		{
			xOffset = 0;
		}
		switch (m_currentState)
		{
		case IdlePlayer:
			yOffset = 0;
			break;
		case MovingPlayer:
			yOffset = 120;
			break;
		case PushingPlayer:
			yOffset = 240;
			break;
		case DyingPlayer:
			yOffset = 360;
			break;
		default:
			break;
		}
	}
}

void SpriteComponent::render()
{
	SDL_Rect dstrect = { m_x, m_y, m_width, m_height };

	SDL_Rect srcrect = { xOffset, yOffset, 120, 120 };

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
	if (loadedSurface.at(m_currentTex)->clip_rect.h - srcrect.h < srcrect.y)
	{
		srcrect.y = 0;
	}
	SDL_RenderCopy(m_screen, m_texture.at(m_currentTex), &srcrect, &dstrect);
}