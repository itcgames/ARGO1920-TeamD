#include "EntityManager.h"

void EntityManager::update()
{
	for (auto& e : entities)
	{
		e->update();
	}
}

void EntityManager::draw(SDL_Renderer* t_screen)
{
	for (auto& e : entities)
	{
		e->render(t_screen);
	}
}

void EntityManager::refresh()
{
	entities.erase(std::remove_if(std::begin(entities), std::end(entities),
		[](const std::unique_ptr<Entity>& mEntity)
	{
		return !mEntity->getAlive();
	}), std::end(entities));
}

Entity& EntityManager::addEntity()
{
	Entity* e = new Entity();
	std::unique_ptr<Entity> uPtr{ e };
	entities.emplace_back(std::move(uPtr));
	return *e;
}
