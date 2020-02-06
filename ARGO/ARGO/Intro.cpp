#include "Intro.h"

void Intro::handleEvents(SDL_Event& t_event)
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

void Intro::update()
{
	
	std::cout << "Intro" << std::endl;
	
}

void Intro::render(SDL_Renderer *t_renderer)
{
	SDL_RenderClear(t_renderer);

	SDL_RenderPresent(t_renderer);
}


void Intro::clean(SDL_Renderer& t_renderer, SDL_Window& t_window)
{
}
