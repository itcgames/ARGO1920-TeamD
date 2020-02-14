#include "EntityManager.h"

void EntityManager::handleEvents( Joystick& stick, std::vector<Vector2> t_mapsize)
{
	m_moveThisFrame = false;
	for (auto& e : entities)
	{
		Entity &tempE = *e.get();

		if (tempE.getComponentString() == "player" && timer == MAX_TIME)
		{
			if (stick.Y() == 1)
			{
				handleMove(tempE, "down");
			}
			else if (stick.X() == 1)
			{
				handleMove(tempE, "right");
			}
			else if (stick.X() == -1)
			{
				handleMove(tempE, "left");
			}
			else if (stick.Y() == -1)
			{
				handleMove(tempE, "up");
			}
			else if (SDL_JoystickGetButton(stick.getStick(), 4) != 0)
			{
				tempE.getComponent<PositionComponent>().setToPreviousPos(); 
				m_moveThisFrame = true;
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
	if (m_moveThisFrame)
	{
		timer = 0;
	}
}

void EntityManager::update()
{
	if(timer < MAX_TIME)
		timer++;
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
void EntityManager::mapCol(Vector2& t_pos, Vector2& t_size)
{
	for (auto& f : entities)
	{
		Entity& tempF = *f.get();
		if (tempF.getComponentString() == "player")
		{
			if (m_colSys.collides(t_pos,
				t_size,
				tempF.getComponent<PositionComponent>().getPosition(),
				tempF.getComponent<BodyComponent>().getSize()))
			{
				tempF.getComponent<PositionComponent>().setToPreviousPos();
				Vector2 pos = tempF.getComponent<PositionComponent>().getPosition();
				Vector2 size = tempF.getComponent<BodyComponent>().getSize();
				tempF.getComponent<SpriteComponent>().setPosAndSize(pos.x, pos.y, size.x, size.y);
			}
		}
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
	m_moveThisFrame = true;
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

int EntityManager::handleWin(int t_levelNum)
{
	for (auto& e : entities)
	{
		Entity& tempE = *e.get();

		if (tempE.getComponentString() == "player")
		{
			for (auto& e2 : entities)
			{
				Entity& tempE2 = *e2.get();

				if (tempE2.getComponentString() == "goal")
				{
					if (m_colSys.collides(tempE.getComponent<PositionComponent>().getPosition(), tempE.getComponent<BodyComponent>().getSize(),
						tempE2.getComponent<PositionComponent>().getPosition(), tempE2.getComponent<BodyComponent>().getSize()))
					{
						t_levelNum++;
					}
				}
			}
		}
	}
	return t_levelNum;
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
