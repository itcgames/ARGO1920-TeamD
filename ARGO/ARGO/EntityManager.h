#pragma once
#include "Entity.h"
#include "Joystick.h"
#include "Vector2.h"
#include "MovementSystem.h"
#include "CollisionSystem.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"

class EntityManager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;
	MovementSystem m_moveSys;
	CollisionSystem m_colSys;
public:
	void handleEvents(Joystick &stick);
	void update();
	void draw(SDL_Renderer* t_screen);
	void refresh();
	Entity& addEntity(std::string t_identifier);
	void handleMove(Entity& t_ent, std::string t_str);
	void handleStop(Entity& t_ent, std::string t_str);
	//Entity getEnt(int t_arrPos);
};

