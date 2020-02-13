#include "EntityManager.h"

void EntityManager::handleEvents( Joystick& stick, std::vector<Vector2> t_mapsize)
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
				else if (SDL_JoystickGetButton(stick.getStick(), 4) != 0)
				{
					tempE.getComponent<PositionComponent>().setToPreviousPos();
				}
				handleBoundary(tempE, t_mapsize.at(0), t_mapsize.at(1));
		}
		if (tempE.getComponentString() == "stop")
		{
			for (auto& f : entities)
			{
				Entity& tempF = *f.get();
				if (tempF.getComponentString() == "player")
				{
					if (m_colSys.collides(tempE.getComponent<PositionComponent>().getPosition(),
						tempE.getComponent<BodyComponent>().getSize(),
						tempF.getComponent<PositionComponent>().getPosition(),
						tempF.getComponent<BodyComponent>().getSize()))
					{
						tempF.getComponent<PositionComponent>().setToPreviousPos();
					}
				}
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
	t_ent.getComponent<PositionComponent>().setPreviousPosition(t_ent.getComponent<PositionComponent>().getPosition());
	t_ent.getComponent<PositionComponent>().setPosition(tempVec);
	t_ent.getComponent<SpriteComponent>().setPosAndSize(t_ent.getComponent<PositionComponent>().getPosition().X(), t_ent.getComponent<PositionComponent>().getPosition().Y(), t_ent.getComponent<BodyComponent>().getSize().X(), t_ent.getComponent<BodyComponent>().getSize().Y());
}

void EntityManager::handleStop( std::string t_str)
{
	/*const Entity tempE = t_ent;
	for (auto& e2 : entities)
	{

		m_colSys.collides(tempE.getComponent<PositionComponent>().getPosition(),t_)
	}*/
}


void EntityManager::handleBoundary(Entity& t_ent, Vector2 t_mapTopLeft, Vector2 t_mapBottomRight)
{
	Vector2 tempPos = m_boundSys.hitBoundary(t_ent.getComponent<PositionComponent>().getPosition(), t_ent.getComponent<BodyComponent>().getSize(), t_mapTopLeft, t_mapBottomRight);
	t_ent.getComponent<PositionComponent>().setPosition(tempPos);
	t_ent.getComponent<SpriteComponent>().setPosAndSize(t_ent.getComponent<PositionComponent>().getPosition().X(), t_ent.getComponent<PositionComponent>().getPosition().Y(), t_ent.getComponent<BodyComponent>().getSize().X(), t_ent.getComponent<BodyComponent>().getSize().Y());
}

//Entity EntityManager::getEnt(int t_arrPos)
//{
//	return *entities[t_arrPos];
//}
