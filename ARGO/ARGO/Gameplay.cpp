#include "Gameplay.h"

void Gameplay::init(SDL_Renderer*& t_renderer)
{
	m_map.init(t_renderer);
	m_sprite.loadFromFile("ASSETS/player.bmp", t_renderer);
}

void Gameplay::handleEvents(SDL_Event& t_event)
{
	switch (t_event.type)
	{
	case SDL_KEYDOWN:
		if (t_event.key.keysym.sym == SDLK_ESCAPE)
		{


		}
		break;
	default:
		break;
	}
}

void Gameplay::update()
{
	std::cout << "Gameplay";
}

void Gameplay::render(SDL_Renderer*& t_renderer)
{
	//m_sprite.render(500, 500, t_renderer);
	for (int j = 0; j < 50; j++)
	{
		for (int i = 0; i < 50; i++)
		{
			m_map.render(t_renderer, i, j);
		}
	}
	
}


void Gameplay::clean(SDL_Renderer*& t_renderer, SDL_Window* t_window)
{
}
