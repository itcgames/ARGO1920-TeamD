#include "help.h"

Help::Help()
{
	m_mainMenuTutorialRect = { 0, 0, 1200, 800 };
	m_movementTutorialRect = { 1300, 0, 1200, 800 };
	m_wordsUITutorialRect = { 0, 850, 1200, 800 };
	m_reverseTutorialRect = { 1300, 850, 1200, 800 };
	m_backgroundRect = { 0,0, 3840, 2160 };
	m_backBtnRect = { 3200,1600, 500,500 };
	m_selectorRect = m_backBtnRect;
	loadedSurface = NULL;
	m_backgroundTexture = NULL;
	m_backBtnTexture = NULL;

	currentState = HelpButtonState::helpBackBtn;
	count = 0;
}

void Help::handleEvents(SDL_Event& t_event, GameState& gamestate, Joystick t_stick)
{
	count++;
	switch (t_event.type)
	{
	case SDL_JOYBUTTONDOWN:
		if (SDL_JoystickGetButton(t_stick.getStick(), 1) != 0 && count > 30)
		{
			count = 0;
			switch (currentState)
			{
			case HelpButtonState::helpBackBtn:
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

void Help::update()
{
}

void Help::render(SDL_Renderer* t_renderer)
{
	loadSprites(t_renderer);
	SDL_RenderClear(t_renderer);
	SDL_RenderCopy(t_renderer, m_backgroundTexture, NULL, &m_backgroundRect);
	SDL_RenderCopy(t_renderer, m_backBtnTexture, NULL, &m_backBtnRect);
	SDL_RenderCopy(t_renderer, m_mainMenuTutorialTexture, NULL, &m_mainMenuTutorialRect);
	SDL_RenderCopy(t_renderer, m_wordsUITutorialTexture, NULL, &m_wordsUITutorialRect);
	SDL_RenderCopy(t_renderer, m_reverseTutorialTexture, NULL, &m_reverseTutorialRect);
	SDL_RenderCopy(t_renderer, m_movementTutorialTexture, NULL, &m_movementTutorialRect);
	SDL_RenderPresent(t_renderer);
}

void Help::clean(SDL_Renderer& t_renderer, SDL_Window& t_window)
{
}

void Help::loadSprites(SDL_Renderer* renderer)
{
	if (m_backgroundTexture == NULL)
	{
		loadedSurface = SDL_LoadBMP("ASSETS/IMAGES/helpTutorialBackground.bmp");
		m_backgroundTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		loadedSurface = SDL_LoadBMP("ASSETS/IMAGES/Back.bmp");
		m_backBtnTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		loadedSurface = SDL_LoadBMP("ASSETS/IMAGES/MainMenuTutorial.bmp");
		m_mainMenuTutorialTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		loadedSurface = SDL_LoadBMP("ASSETS/IMAGES/MovementTutorial.bmp");
		m_movementTutorialTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		loadedSurface = SDL_LoadBMP("ASSETS/IMAGES/WordsUITutorial.bmp");
		m_wordsUITutorialTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		loadedSurface = SDL_LoadBMP("ASSETS/IMAGES/ReverseTutorial.bmp");
		m_reverseTutorialTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		SDL_FreeSurface(loadedSurface);
	}
}
