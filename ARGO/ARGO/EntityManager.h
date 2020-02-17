#pragma once
#include "Entity.h"
#include "Joystick.h"
#include "Vector2.h"
#include "MovementSystem.h"
#include "CollisionSystem.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "BoundarySystem.h"
#include "VelocityComponent.h"

class EntityManager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;
	MovementSystem m_moveSys;
	CollisionSystem m_colSys;
	BoundarySystem m_boundSys;

	int timer = 0;
	bool m_moveThisFrame = false;
public:
	void handleEvents(Joystick &stick,std::vector<Vector2> t_mapsize);
	void update();
	void draw(SDL_Renderer* t_screen);
	void refresh();
	Entity& addEntity(std::string t_identifier);
	void handleMove(Entity& t_ent, std::string t_str);
	void mapCol(Vector2& t_pos,Vector2& t_size);

	void handleBoundary(Entity& t_ent, Vector2 t_mapTopLeft, Vector2 t_mapBottomRight);
	void handleStop( std::string t_str);
	int handleWin(int t_levelNum);
	//Entity getEnt(int t_arrPos);
	
	static const int MAX_TIME = 10;
};

