#include "Options.h"

Options::Options()
{
	m_backgroundRect = { 0,0, 3840, 2160 };
	m_backBtnRect = { 3200,1600, 500,500 };
	m_selectorRect = m_backBtnRect;
	loadedSurface = NULL;
	m_backgroundTexture = NULL;
	m_backBtnTexture = NULL;
	m_selectorTexture = NULL;

	currentState = OptionsButtonState::optionsBackBtn;
	count = 0;
}

void Options::handleEvents(SDL_Event& t_event, GameState& gamestate, Joystick t_stick)
{
	count++;
	switch (t_event.type)
	{
	case SDL_JOYBUTTONDOWN:
		if (SDL_JoystickGetButton(t_stick.getStick(), 0) != 0 && count > 30)
		{
			count = 0;
			switch (currentState)
			{
			case OptionsButtonState::optionsBackBtn:
				gamestate = GameState::mainMenu;
			default:
				break;
			}
		}
		break;

	default:
		break;
	}
}

void Options::update()
{

	std::cout << "Options" << std::endl;

}

void Options::render(SDL_Renderer* t_renderer)
{
	loadSprites(t_renderer);
	SDL_RenderClear(t_renderer);
	SDL_RenderCopy(t_renderer, m_backgroundTexture, NULL, &m_backgroundRect);
	SDL_RenderCopy(t_renderer, m_backBtnTexture, NULL, &m_backBtnRect);
	SDL_RenderCopy(t_renderer, m_selectorTexture, NULL, &m_selectorRect);
	SDL_RenderPresent(t_renderer);
}


void Options::clean(SDL_Renderer& t_renderer, SDL_Window& t_window)
{
}

void Options::loadSprites(SDL_Renderer* renderer)
{
	if (m_backgroundTexture == NULL)
	{
		loadedSurface = SDL_LoadBMP("ASSETS/IMAGES/options.bmp");
		m_backgroundTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		loadedSurface = SDL_LoadBMP("ASSETS/IMAGES/selector.bmp");
		m_selectorTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		loadedSurface = SDL_LoadBMP("ASSETS/IMAGES/Back.bmp");
		m_backBtnTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		SDL_FreeSurface(loadedSurface);
	}
}
