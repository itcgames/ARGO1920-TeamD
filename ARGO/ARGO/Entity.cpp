#include "Entity.h"
#include "SpriteComponent.h"
Entity::Entity()
{
	//uniqueID = componentIDCounter++;
}

bool Entity::getAlive()
{
	return alive;
}

void Entity::destroy()
{
	alive = false;
}

//int Entity::getUniqueID()
//{
//	return uniqueID;
//}

void Entity::update()
{
	for (auto& c : components)c->update();
	
}

void Entity::render(SDL_Renderer* t_screen)
{
	for (auto& c : components)c->render();
}
