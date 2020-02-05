#include "Entity.h"

Entity::Entity()
{
	uniqueID = componentIDCounter++;
}

bool Entity::getAlive()
{
	return alive;
}

void Entity::setAliveFalse()
{
	alive = false;
}

int Entity::getUniqueID()
{
	return uniqueID;
}

void Entity::update()
{
	for (auto& c : components)c->update();
	for (auto& c : components)c->render();
}

void Entity::render()
{
}
