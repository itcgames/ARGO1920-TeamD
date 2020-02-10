#include "MainMenu.h"

MainMenu::MainMenu()
{
	m_x = 0;
	m_y = 0;
	m_width = 3840;
	m_height = 2160;
	loadedSurface = NULL;
	m_texture = NULL;

	loadedSurface = SDL_LoadBMP("ASSETS/IMAGES/mainmenu.bmp");
}

void MainMenu::handleEvents(SDL_Event& t_event)
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

void MainMenu::update()
{

	std::cout << "MainMenu" << std::endl;

}

void MainMenu::render(SDL_Renderer* t_renderer)
{
	SDL_RenderClear(t_renderer);
	SDL_Rect dstrect = { m_x, m_y, m_width, m_height };
	if (m_texture == NULL)
	{
		m_texture = SDL_CreateTextureFromSurface(t_renderer, loadedSurface);
	}
	SDL_RenderCopy(t_renderer, m_texture, NULL, &dstrect);
	SDL_RenderPresent(t_renderer);
}


void MainMenu::clean(SDL_Renderer& t_renderer, SDL_Window& t_window)
{
}
