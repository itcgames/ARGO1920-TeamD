#include "Gameplay.h"
#include <fstream>
#include <sstream>
Gameplay::Gameplay() :
	myClient("Q", 1111)//149.153.106.148
{
	if (!myClient.Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;
	}
	mess = "";
}

void Gameplay::init(SDL_Renderer*& t_renderer)
{
	m_map.init(t_renderer);
	m_map.setLevelNum(1);
	m_pauseMenu.setRules(m_map.getLevelNum());
	std::string temp = "ASSETS/IMAGES/level" + std::to_string(m_map.getLevelNum()) + "back.bmp";
	m_loadedSurfaceBack = SDL_LoadBMP(temp.c_str());
	m_textureBack = SDL_CreateTextureFromSurface(t_renderer, m_loadedSurfaceBack);
	m_pauseMenu.init();
	timer = 0;
	m_OTree.initTree(Vector2(0, 0), Vector2(960, 1080), Vector2(960, 0), Vector2(1920, 0), Vector2(2840, 0), Vector2(0, 900), Vector2(960, 900), Vector2(1920, 900), Vector2(2840, 900));

	m_ghosts.setUp(t_renderer);
}

void Gameplay::handleEvents(SDL_Event& t_event, GameState& gamestate, Joystick t_stick)
{
	if (SDL_JoystickGetButton(t_stick.getStick(), 6) != 0)
	{
		gamestate = GameState::mainMenu;
	}
	m_pauseMenu.input(t_event, t_stick);
}

void Gameplay::update()
{
	m_pauseMenu.update();
	
	if (myClient.isMessage)
	{
		myClient.isMessage = false;
		if (m_ghosts.update(myClient.newMessage, playerNum) == playerNum)
		{
			playerNum++;
		}
		//m_pauseMenu.otherUIRules(myClient.newMessage);
	}
	std::istringstream input;
	input.str(mess);
	std::string message = "";
	std::getline(input, message, ':');
	if (std::stoi(message) == playerNum)
	{
		myClient.SendString(mess);
	}
	std::cout << mess << std::endl;

	m_map.BFS(Vector2(1,1));
}

void Gameplay::render(SDL_Renderer*& t_renderer, EntityManager& t_entMan)
{
	int newLevel = t_entMan.handleWin(m_map.getLevelNum());
	if (m_map.getLevelNum() != newLevel)
	{
		m_map.init(t_renderer,newLevel);
		m_pauseMenu.setRules(m_map.getLevelNum());
		std::string temp = "ASSETS/IMAGES/level" + std::to_string(m_map.getLevelNum()) + "back.bmp";
		m_loadedSurfaceBack = SDL_LoadBMP(temp.c_str());
		m_textureBack = SDL_CreateTextureFromSurface(t_renderer, m_loadedSurfaceBack);
	}
	SDL_Rect dstrect = { 120, 120, m_map.getMapCorners().at(1).x-120,  m_map.getMapCorners().at(1).y-120};

	SDL_RenderCopy(t_renderer, m_textureBack, NULL, &dstrect);
	for (int j=0; j < 15; j++)
	{
		for (int i=0; i < 32; i++)
		{
			m_map.render(t_renderer, i, j);
			Vector2 temp(120, 120);

		}
	}
	m_pauseMenu.render(t_renderer);
	//m_ghosts.render();
}

void Gameplay::clean(SDL_Renderer*& t_renderer, SDL_Window* t_window)
{
}


std::vector<std::string> Gameplay::getChanges()
{
	return m_pauseMenu.getChanges();
}

Map Gameplay::getMap()
{
	return m_map;
}

std::vector<Vector2> Gameplay::getMapCorners()
{
	return m_map.getMapCorners();
}

void Gameplay::fixedUpdate(EntityManager& t_entMan)
{
	Vector2 PlayerPos = t_entMan.getPlayerPos();
	for (int i = 0; i < 8; i++)
	{
		if (gameplayCol.collides(m_OTree.getOct(i), m_OTree.getSize(), PlayerPos, Vector2(120, 120)))
		{
			setupRowCol(0, 0, 15, 32);
			int test;
			//row,col,maxrow,maxcol
			if (i == 0) {
				setupRowCol(0, 0, 7, 8);

			}if (i == 1) {
				setupRowCol(0, 8, 7, 16);
			}if (i == 2) {
				setupRowCol(0, 16, 7, 24);
			}if (i == 3) {
				setupRowCol(0, 24, 7, 32);
			}if (i == 4) {
				setupRowCol(7, 0, 15, 8);
			}if (i == 5) {
				setupRowCol(7, 8, 15, 16);
			}if (i == 6) {
				setupRowCol(7, 16, 15, 24);
			}if (i == 7) {
				setupRowCol(7, 24, 15, 32);
			}
		}
	}
	for (int j = row; j < maxRow; j++)
	{
		for (int i = col; i < maxCol; i++)
		{
			Vector2 temp(120, 120);
			t_entMan.mapCol(m_map.tile[i][j].vec, temp);
		}
	}
}

void Gameplay::updatePositions(std::vector<Vector2> t_pos)
{
	mess = std::to_string(playerNum) + ":Cat-" + std::to_string(int(t_pos.at(0).x)) + "," + std::to_string(int(t_pos.at(0).y)) + ","
		+ "Clock-" + std::to_string(int(t_pos.at(1).x)) + "," + std::to_string(int(t_pos.at(1).y)) + ","
		+ "Book-" + std::to_string(int(t_pos.at(2).x)) + "," + std::to_string(int(t_pos.at(2).y)) + ","
		+ "Flag-" + std::to_string(int(t_pos.at(3).x)) + "," + std::to_string(int(t_pos.at(3).y)) + ","
		+ "Cactus-" + std::to_string(int(t_pos.at(4).x)) + "," + std::to_string(int(t_pos.at(4).y)) + ",";
}

void Gameplay::setupRowCol(int t_row, int t_col, int t_MaxRow,int t_MaxCol)
{
	row = t_row;
	col = t_col;
	maxRow = t_MaxRow;
	maxCol = t_MaxCol;
}
