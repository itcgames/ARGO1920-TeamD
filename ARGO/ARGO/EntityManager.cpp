#include "EntityManager.h"

void EntityManager::handleEvents( Joystick& stick)
{
	
	for (auto& e : entities)
	{
		Entity &tempE = *e.get();
		
			if (tempE.getComponentString() == "player")
			{
				if (SDL_JoystickGetButton(stick.getStick(), 0) != 0)
				{
					handleMove(tempE, "down");
				}
				else if (SDL_JoystickGetButton(stick.getStick(), 1) != 0)
				{
					handleMove(tempE, "right");
				}
				else if (SDL_JoystickGetButton(stick.getStick(), 2) != 0)
				{
					handleMove(tempE, "left");
				}
				else if (SDL_JoystickGetButton(stick.getStick(), 3) != 0)
				{
					handleMove(tempE, "up");
				}
			}
		
	}
	
}

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

Entity& EntityManager::addEntity(std::string t_identifier)
{
	Entity* e = new Entity();
	std::unique_ptr<Entity> uPtr{ e };
	entities.emplace_back(std::move(uPtr));
	e->setComponentString(t_identifier);
	return *e;
}

void EntityManager::handleMove(Entity& t_ent, std::string t_str)
{
	Vector2 tempVec = m_moveSys.move(t_ent.getComponent<PositionComponent>().getPosition(), t_str);
	t_ent.getComponent<PositionComponent>().setPosition(tempVec);
	t_ent.getComponent<SpriteComponent>().setPosAndSize(t_ent.getComponent<PositionComponent>().getPosition().X(), t_ent.getComponent<PositionComponent>().getPosition().Y(), t_ent.getComponent<BodyComponent>().getSize().X(), t_ent.getComponent<BodyComponent>().getSize().Y());
}

void EntityManager::handleStop(Entity &  t_ent, std::string t_str)
{
	/*Entity tempE = t_ent;
	for (auto& e2 : entities)
	{

		m_colSys.collides(tempE.getComponent<PositionComponent>().getPosition(),t_)
	}*/
}

//Entity EntityManager::getEnt(int t_arrPos)
//{
//	return *entities[t_arrPos];
//}

