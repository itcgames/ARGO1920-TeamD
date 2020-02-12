#pragma once
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Gamestate.h"

enum HelpButtonState
{
	helpBackBtn
};

class Help
{
public:
	Help();
	void handleEvents(SDL_Event& t_event, GameState& gamestate);
	void update();
	void render(SDL_Renderer* t_renderer);
	void clean(SDL_Renderer& t_renderer, SDL_Window& t_window);
	void loadSprites(SDL_Renderer* renderer);
private:
	SDL_Surface* loadedSurface;
	SDL_Texture* m_backgroundTexture;
	SDL_Texture* m_backBtnTexture;
	SDL_Texture* m_selectorTexture;
	SDL_Rect m_backgroundRect;
	SDL_Rect m_backBtnRect;
	SDL_Rect m_selectorRect;

	HelpButtonState currentState;
	int count;
};

