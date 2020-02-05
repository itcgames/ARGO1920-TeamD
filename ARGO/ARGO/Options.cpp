#include "Options.h"

void Options::handleEvents(SDL_Event& t_event)
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

void Options::update()
{

	std::cout << "Options" << std::endl;

}

void Options::render(SDL_Renderer* t_renderer)
{
	SDL_RenderClear(t_renderer);

	SDL_RenderPresent(t_renderer);
}


void Options::clean(SDL_Renderer& t_renderer, SDL_Window& t_window)
{
}
