#pragma once
#include "Entity.h"
#include "Joystick.h"
#include "Vector2.h"
#include "MovementSystem.h"
#include "CollisionSystem.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "BoundarySystem.h"
#include "BotComponent.h"

#include"Up.h"
#include"Down.h"
#include"Left.h"
#include"Right.h"

class EntityManager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;
	MovementSystem m_moveSys;
	BoundarySystem m_boundSys;


	float timer = 0;
	float newTimer = 1;
	bool m_moveThisFrame = false;
	bool m_inputThisFrame = false;
	bool m_startOfInput = false;
	bool m_diedToCactus = false;
	std::string m_direction = "";

	UpCommand m_up;
	DownCommand m_down;
	LeftCommand m_left;
	RightCommand m_right;
	static int  currBiggestStack;
	bool firstRun = false;
public:
	void handleEvents(Joystick &stick,std::vector<Vector2> t_mapsize);
	void update(int yVal, int xVal, int hVal, int wVal);
	void draw(SDL_Renderer* t_screen);
	void refresh();
	Entity& addEntity(std::string t_identifier);
	void handleMove(Entity& t_ent, std::string t_str);
	void mapCol(Vector2& t_pos,Vector2& t_size);

	void handleBoundary(Entity& t_ent, Vector2 t_mapTopLeft, Vector2 t_mapBottomRight);
	void movement();
	void pushing();
	void dying();
	int handleWin(int t_levelNum);
	bool GetDeathToCactus() { return m_diedToCactus; }
	
	
	//Entity getEnt(int t_arrPos);


	
	CollisionSystem m_colSys;
	Vector2 getPlayerPos() {
		for (auto& f : entities)
		{
			Entity& tempF = *f.get();
			if (tempF.getComponentString() == "player")
			{
				return tempF.getComponent<PositionComponent>().getPosition();
			};
		}
	}
	
	static const int MAX_TIME = 10;
	int fakeStickXVal = -1;
};
