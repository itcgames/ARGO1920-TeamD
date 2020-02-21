#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Map.h"
#include "PauseMenu.h"
#include "Joystick.h"
#include "EntityManager.h"
#include "Gamestate.h"
#include "OctTree.h"
#include "CollisionSystem.h"
#include "ClientStuff/Client.h"
class Gameplay
{
public:
	Gameplay();

	void init(SDL_Renderer*& t_renderer);
	void handleEvents(SDL_Event& t_event, GameState& gamestate, Joystick t_stick);
	void update();
	void render(SDL_Renderer *&t_renderer,EntityManager& t_entMan);

	void clean(SDL_Renderer*& t_renderer, SDL_Window* t_window);
	std::vector<std::string> getChanges();
	Map getMap();
	std::vector<Vector2> getMapCorners();
	void fixedUpdate(EntityManager& t_entMan);
private:
	Map m_map;
	PauseMenu m_pauseMenu;
	int timer;
	OctTree m_OTree;
	int row, col,maxRow,maxCol;
	void setupRowCol(int t_row, int t_col, int t_MaxRow, int t_MaxCol);
	CollisionSystem gameplayCol;
	SDL_Surface* m_loadedSurfaceBack;
	SDL_Texture* m_textureBack;
	Client myClient;
	int playerNum = 1;
};