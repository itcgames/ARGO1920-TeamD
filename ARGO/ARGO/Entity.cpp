#include "Entity.h"

bool Entity::getAlive()
{
	return alive;
}

void Entity::setAliveFalse()
{
	alive = false;
}

void Entity::update()
{
	for (auto& c : components)c->update();
	for (auto& c : components)c->render();
}

void Entity::render()
{
}
