#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Gamestate.h"
#include "LevelState.h"
#include "SpriteComponent.h"
#include "PositionComponent.h"
#include "EntityManager.h"

#include "Intro.h"
#include "Splash.h"
#include "MainMenu.h"
#include "Gameplay.h"
#include "Options.h"
#include "Credits.h"
#include "Joystick.h"
#include "MovementSystem.h"
class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }
	static GameState m_currentMode;
	static LevelState m_currentLevel;

	SDL_Renderer* m_renderer;
	SDL_Event m_event;
private:
	bool isRunning;
	SDL_Window* m_window;
	Intro m_introScr;
	Splash m_splashScr;
	MainMenu m_mainMenuScr;
	Gameplay m_gamePlayScr;
	Options m_optionsScr;
	Credits m_creditsScr;

	Joystick stick;
	bool keyTest = false;

	Entity* m_cat;


	/// <summary>
	/// Systems
	/// </summary>
	MovementSystem m_moveSys;
	void handleMove(Entity &t_ent, std::string t_str);
};
