#include "Gameplay.h"

void Gameplay::init(SDL_Renderer*& t_renderer)
{
	m_map.init(t_renderer);
	m_pauseMenu.init();
	paused = false;
	timer = 0;
	m_OTree.initTree(Vector2(0, 0), Vector2(960, 1080), Vector2(960, 0), Vector2(1920, 0), Vector2(2840, 0), Vector2(0, 1080), Vector2(960, 1080), Vector2(1920, 1080), Vector2(2840, 1080));
}

void Gameplay::handleEvents(SDL_Event& t_event, GameState& gamestate, Joystick t_stick)
{
	if (SDL_JoystickGetButton(t_stick.getStick(), 6) != 0)
	{
		gamestate = GameState::mainMenu;
	}
	if (SDL_JoystickGetButton(t_stick.getStick(), 7) != 0 && m_pauseMenu.getTime() >= m_pauseMenu.MAX_TIME)
	{
		paused = !paused;
		m_pauseMenu.resetTime();
	}
	if (paused)
	{
		m_pauseMenu.input(t_event, t_stick);
	}
}

void Gameplay::update()
{
	std::cout << "Gameplay" << std::endl;
	m_pauseMenu.update();
}

void Gameplay::render(SDL_Renderer*& t_renderer, EntityManager& t_entMan)
{
	int newLevel = t_entMan.handleWin(m_map.getLevelNum());
	if (m_map.getLevelNum() != newLevel)
	{
		m_map.init(t_renderer,newLevel);
	}
	Vector2 PlayerPos = t_entMan.getPlayerPos();
	for (int i = 0; i < 8; i++)
	{
		if (gameplayCol.collides(m_OTree.getOct(i), m_OTree.getSize(), PlayerPos, Vector2(120, 120)))
		{
			int test;
			//row,col,maxrow,maxcol
			if (i == 0){
				setupRowCol(0, 0, 9, 8);
				
			}if (i == 1) {
				setupRowCol(0, 8, 9, 16);
			}if (i == 2) {
				setupRowCol(0, 16, 9, 24);
			}if (i == 3) {
				setupRowCol(0, 24, 9, 32);
			}if (i == 4) {
				setupRowCol(9, 0, 18, 8);
			}if (i == 5) {
				setupRowCol(9, 8, 18, 16);
			}if (i == 6) {
				setupRowCol(9, 16, 18, 24);
			}if (i == 7) {
				setupRowCol(9, 24, 18, 32);
			}
		}
	}
	for (int j=row; j < maxRow; j++)
	{
		for (int i=col; i < maxCol; i++)
		{
			m_map.render(t_renderer, i, j);
			Vector2 temp(120, 120);
			t_entMan.mapCol(m_map.tile[i][j].vec,temp );
		}
	}
}

void Gameplay::renderUI(SDL_Renderer*& t_renderer)
{
	if (paused)
	{
		m_pauseMenu.render(t_renderer);
	}
}


void Gameplay::clean(SDL_Renderer*& t_renderer, SDL_Window* t_window)
{
}

bool Gameplay::isPaused()
{
	return paused;
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

void Gameplay::setupRowCol(int t_row, int t_col, int t_MaxRow,int t_MaxCol)
{
	row = t_row;
	col = t_col;
	maxRow = t_MaxRow;
	maxCol = t_MaxCol;
}
