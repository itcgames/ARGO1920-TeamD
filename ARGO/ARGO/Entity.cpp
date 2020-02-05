#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::update()
{
	for (auto& c : components) c->update();
	for (auto& c : components) c->render();
}

void Entity::draw()
{
	
}

void Entity::getActive()
{
	return active;
}

void Entity::setActiveFalse()
{
	active = false;
}
