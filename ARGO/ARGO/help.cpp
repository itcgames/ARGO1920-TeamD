#include "help.h"

Help::Help()
{
	m_backgroundRect = { 0,0, 3840, 2160 };
	loadedSurface = NULL;
	m_backgroundTexture = NULL;
}

void Help::handleEvents(SDL_Event& t_event, GameState& gamestate)
{
	switch (t_event.type)
	{
	case SDL_KEYDOWN:
		if (t_event.key.keysym.sym == SDLK_ESCAPE)
		{
			SDL_Quit();
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
		SDL_FreeSurface(loadedSurface);
	}
}
