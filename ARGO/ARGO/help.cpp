#include "help.h"

Help::Help()
{
	m_backgroundRect = { 0,0, 3840, 2160 };
	m_backBtnRect = { 3200,1600, 500,500 };
	m_selectorRect = m_backBtnRect;
	loadedSurface = NULL;
	m_backgroundTexture = NULL;
	m_backBtnTexture = NULL;
	m_selectorTexture = NULL;

	currentState = HelpButtonState::helpBackBtn;
	count = 0;
}

void Help::handleEvents(SDL_Event& t_event, GameState& gamestate)
{
	count++;
	switch (t_event.type)
	{
	case SDL_KEYDOWN:
		if (t_event.key.keysym.sym == SDLK_ESCAPE)
		{
			SDL_Quit();
		}

		if (t_event.key.keysym.sym == SDLK_RETURN && count > 60)
		{
			switch (currentState)
			{
			case HelpButtonState::helpBackBtn:
				gamestate = GameState::mainMenu;
				break;
			default:
				break;
			}

			count = 0;
		}
		break;
	default:
		break;
	}
}

void Help::update()
{
}

void Help::render(SDL_Renderer* t_renderer)
{
	loadSprites(t_renderer);
	SDL_RenderClear(t_renderer);
	SDL_RenderCopy(t_renderer, m_backgroundTexture, NULL, &m_backgroundRect);
	SDL_RenderCopy(t_renderer, m_backBtnTexture, NULL, &m_backBtnRect);
	SDL_RenderCopy(t_renderer, m_selectorTexture, NULL, &m_selectorRect);
	SDL_RenderPresent(t_renderer);
}

void Help::clean(SDL_Renderer& t_renderer, SDL_Window& t_window)
{
}

void Help::loadSprites(SDL_Renderer* renderer)
{
	if (m_backgroundTexture == NULL)
	{
		loadedSurface = SDL_LoadBMP("ASSETS/IMAGES/helpBackground.bmp");
		m_backgroundTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		loadedSurface = SDL_LoadBMP("ASSETS/IMAGES/selector.bmp");
		m_selectorTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		loadedSurface = SDL_LoadBMP("ASSETS/IMAGES/Back.bmp");
		m_backBtnTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		SDL_FreeSurface(loadedSurface);
	}
}
