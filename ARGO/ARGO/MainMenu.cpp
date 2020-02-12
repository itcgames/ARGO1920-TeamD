#include "MainMenu.h"

MainMenu::MainMenu()
{
	m_backgroundRect = { 0,0, 3840, 2160 };
	m_playRect = { 1200,100,643 * 2,215 * 2 };
	m_optionsRect = { 1200,650,643 * 2,215 * 2};
	m_helpRect = { 1200,1200,643 * 2,215 * 2};
	m_quitRect = { 1200,1750,643 * 2,215 * 2 };
	m_selectorRect = m_playRect;

	loadedSurface = NULL;
	m_backgroundTexture = NULL;

	currentState = ButtonState::play;
}

void MainMenu::handleEvents(SDL_Event& t_event, GameState& gamestate)
{
	switch (t_event.type)
	{
	case SDL_KEYDOWN:
		if (t_event.key.keysym.sym == SDLK_ESCAPE)
		{

		}
		if (t_event.key.keysym.sym == SDLK_DOWN)
		{
			switch (currentState)
			{
			case ButtonState::play:
				currentState = ButtonState::optionsBTN;
				break;
			case ButtonState::optionsBTN:
				currentState = ButtonState::help;
				break;
			case ButtonState::help:
				currentState = ButtonState::quit;
				break;
			case ButtonState::quit:
				currentState = ButtonState::play;
				break;
			default:
				break;
			}
		}

		if (t_event.key.keysym.sym == SDLK_UP)
		{
			switch (currentState)
			{
			case ButtonState::play:
				currentState = ButtonState::quit;
				break;
			case ButtonState::quit:
				currentState = ButtonState::help;
				break;
			case ButtonState::help:
				currentState = ButtonState::optionsBTN;
				break;
			case ButtonState::optionsBTN:
				currentState = ButtonState::play;
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
}

void MainMenu::update()
{
	switch (currentState)
	{
	case ButtonState::play:
		m_selectorRect = m_playRect;
		break;
	case ButtonState::optionsBTN:
		m_selectorRect = m_optionsRect;
		break;
	case ButtonState::help:
		m_selectorRect = m_helpRect;
		break;
	case ButtonState::quit:
		m_selectorRect = m_quitRect;
		break;
	default:
		break;
	}
}

void MainMenu::render(SDL_Renderer* t_renderer)
{
	SDL_RenderClear(t_renderer);
	loadSprites(t_renderer);

	SDL_RenderCopy(t_renderer, m_backgroundTexture, NULL, &m_backgroundRect);
	SDL_RenderCopy(t_renderer, m_playTexture, NULL, &m_playRect);
	SDL_RenderCopy(t_renderer, m_optionsTexture, NULL, &m_optionsRect);
	SDL_RenderCopy(t_renderer, m_helpTexture, NULL, &m_helpRect);
	SDL_RenderCopy(t_renderer, m_quitTexture, NULL, &m_quitRect);
	SDL_RenderCopy(t_renderer, m_selectorTexture, NULL, &m_selectorRect);
	SDL_RenderPresent(t_renderer);
}


void MainMenu::clean(SDL_Renderer& t_renderer, SDL_Window& t_window)
{
}

void MainMenu::loadSprites(SDL_Renderer* renderer)
{
	if (m_backgroundTexture == NULL)
	{
		loadedSurface = SDL_LoadBMP("ASSETS/IMAGES/mainmenu.bmp");
		m_backgroundTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		loadedSurface = SDL_LoadBMP("ASSETS/IMAGES/play.bmp");
		m_playTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		loadedSurface = SDL_LoadBMP("ASSETS/IMAGES/options.bmp");
		m_optionsTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		loadedSurface = SDL_LoadBMP("ASSETS/IMAGES/help.bmp");
		m_helpTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		loadedSurface = SDL_LoadBMP("ASSETS/IMAGES/quit.bmp");
		m_quitTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		loadedSurface = SDL_LoadBMP("ASSETS/IMAGES/selector.bmp");
		m_selectorTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		SDL_FreeSurface(loadedSurface);

	}
}
