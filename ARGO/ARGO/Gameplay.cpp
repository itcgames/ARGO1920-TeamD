#include "Gameplay.h"
#include <fstream>
#include <sstream>
Gameplay::Gameplay() :
	myClient("149.153.106.148", 1111)//149.153.106.148
{
	if (!myClient.Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;
	}
	mess = "";
}

void Gameplay::init(SDL_Renderer*& t_renderer)
{


	m_map.init(t_renderer,1);
	m_map.setLevelNum(1);
	m_pauseMenu.setRules(m_map.getLevelNum());
	std::string temp = "ASSETS/IMAGES/level" + std::to_string(m_map.getLevelNum()) + "back.bmp";
	m_loadedSurfaceBack = SDL_LoadBMP(temp.c_str());
	m_textureBack = SDL_CreateTextureFromSurface(t_renderer, m_loadedSurfaceBack);
	m_pauseMenu.init();
	timer = 0;
	m_OTree.initTree(Vector2(0, 0), Vector2(960, 1080));

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

	/*if (myClient.isMessage)
	{
		myClient.isMessage = false;
		if (m_ghosts.update(myClient.newMessage, playerNum) == playerNum)
		{
			playerNum++;
		}
	}
	std::istringstream input;
	input.str(mess);
	std::string message = "";
	std::getline(input, message, ':');
	if (std::stoi(message) == playerNum)
	{
		myClient.SendString(mess);
	}
	std::string ip = myClient.GetIPAddr();*/
}

void Gameplay::render(SDL_Renderer*& t_renderer, EntityManager& t_entMan)
{
	 newLevel = t_entMan.handleWin(m_map.getLevelNum());
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
	m_ghosts.render();
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

	int xVal, yVal, wVal, hVal;
	xVal = (PlayerPos.X() - 240) / 120;
	yVal = (PlayerPos.Y() - 240) / 120;
	wVal = (PlayerPos.X() + 360) / 120;
	hVal = (PlayerPos.Y() + 360) / 120;
	if (xVal < 0)
	{
		xVal = 0;
	}
	if (yVal < 0)
	{
		yVal = 0;
	}
	if (wVal > 32)
	{
		wVal = 32;
	}
	if (hVal > 15)
	{
		hVal = 15;
	}
	setupRowCol(yVal, xVal, hVal, wVal);
	bool updateCalled = false;
	for (int j = row; j < maxRow; j++)
	{
		for (int i = col; i < maxCol; i++)
		{
			Vector2 temp(120, 120);
			t_entMan.mapCol(m_map.tile[i][j].vec, temp);
			if (!updateCalled)
			{
				t_entMan.update(yVal, xVal, hVal, wVal);
				updateCalled = true;
			}

		}
	}


}

bool Gameplay::getSwappedStates()
{
	m_stateSwapped = m_pauseMenu.getStatesSwapped();
	return m_stateSwapped;
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
