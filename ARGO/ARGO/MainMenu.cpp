#include "MainMenu.h"

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

	SDL_RenderPresent(t_renderer);
}


void MainMenu::clean(SDL_Renderer& t_renderer, SDL_Window& t_window)
{
}
