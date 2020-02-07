#pragma once
#include "Entity.h"
class EntityManager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;

public:
	void update();
	void draw();
	void refresh();
	Entity& addEntity();
};

