#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Gamestate.h"
#include "LevelState.h"
#include "Sprite.h"

#include "Intro.h"
#include "Splash.h"
#include "MainMenu.h"
#include "Options.h"
#include "Credits.h"

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
	Options m_optionsScr;
	Credits m_creditsScr;

	bool keyTest = false;

	Sprite spriteTemp;
};
