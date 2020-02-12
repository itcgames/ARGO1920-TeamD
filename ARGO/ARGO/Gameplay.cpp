#include "Gameplay.h"

void Gameplay::init(SDL_Renderer*& t_renderer)
{
	m_map.init(t_renderer);
	m_pauseMenu.init();
	paused = false;
	timer = 0;
}

void Gameplay::handleEvents(SDL_Event& t_event, Joystick t_stick)
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
	if (SDL_JoystickGetButton(t_stick.getStick(), 7) != 0 && m_pauseMenu.getTime() >= m_pauseMenu.TIME_SPEED)
	{
		paused = !paused;
		m_pauseMenu.resetTime();
	}
	if (paused)
	{
		m_pauseMenu.input(t_event, t_stick);
	}
}

void Gameplay::update()
{
	std::cout << "Gameplay" << std::endl;
	m_pauseMenu.update();
}

void Gameplay::render(SDL_Renderer*& t_renderer)
{
	for (int j = 0; j < 50; j++)
	{
		for (int i = 0; i < 50; i++)
		{
			m_map.render(t_renderer, i, j);
		}
	}
	if (paused)
	{
		m_pauseMenu.render(t_renderer);
	}
}


void Gameplay::clean(SDL_Renderer*& t_renderer, SDL_Window* t_window)
{
}

bool Gameplay::isPaused()
{
	return paused;
}

std::vector<std::string> Gameplay::getChanges()
{
	return m_pauseMenu.getChanges();
}
