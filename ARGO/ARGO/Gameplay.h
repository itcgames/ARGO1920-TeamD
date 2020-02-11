#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Map.h"
#include "PauseMenu.h"
#include "Joystick.h"
class Gameplay
{
public:
	void init(SDL_Renderer*& t_renderer);
	void handleEvents(SDL_Event& t_event, Joystick t_stick);
	void update();
	void render(SDL_Renderer *&t_renderer);
	void clean(SDL_Renderer*& t_renderer, SDL_Window* t_window);
	bool isPaused();
private:
	Map m_map;
	PauseMenu m_pauseMenu;
	bool paused;
	int timer;
};