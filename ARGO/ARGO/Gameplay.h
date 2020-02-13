#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Map.h"
#include "PauseMenu.h"
#include "Joystick.h"
#include "EntityManager.h"
class Gameplay
{
public:
	void init(SDL_Renderer*& t_renderer);
	void handleEvents(SDL_Event& t_event, Joystick t_stick);
	void update();
	void render(SDL_Renderer *&t_renderer,EntityManager& t_entMan);
	void clean(SDL_Renderer*& t_renderer, SDL_Window* t_window);
	bool isPaused();
	std::vector<std::string> getChanges();
	std::vector<Vector2> getMapCorners();
private:
	Map m_map;
	PauseMenu m_pauseMenu;
	bool paused;
	int timer;
};