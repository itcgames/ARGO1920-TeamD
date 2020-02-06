#include "Credits.h"

void Credits::handleEvents(SDL_Event& t_event)
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

void Credits::update()
{

	std::cout << "Credits" << std::endl;

}

void Credits::render(SDL_Renderer* t_renderer)
{
	SDL_RenderClear(t_renderer);

	SDL_RenderPresent(t_renderer);
}


void Credits::clean(SDL_Renderer& t_renderer, SDL_Window& t_window)
{
}
