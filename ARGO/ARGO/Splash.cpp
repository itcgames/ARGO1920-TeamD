#include "Splash.h"

void Splash::handleEvents(SDL_Event& t_event)
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

void Splash::update()
{

	std::cout << "Splash" << std::endl;

}

void Splash::render(SDL_Renderer* t_renderer)
{
	SDL_RenderClear(t_renderer);

	SDL_RenderPresent(t_renderer);
}


void Splash::clean(SDL_Renderer& t_renderer, SDL_Window& t_window)
{
}
