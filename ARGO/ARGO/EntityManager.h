#pragma once
#include "Entity.h"
class EntityManager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;

public:
	void update();
	void draw(SDL_Renderer* t_screen);
	void refresh();
	Entity& addEntity();
};

