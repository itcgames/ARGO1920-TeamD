#include "EntityManager.h"

void EntityManager::handleEvents( Joystick& stick, std::vector<Vector2> t_mapsize)
{

	Entity& tempG = *entities[0];
	Vector2 playerPos;
	for (auto& e : entities)
	{
		Entity& tempG = *e.get();
		if (tempG.getComponentString() == "player")
		{
			playerPos = tempG.getComponent<PositionComponent>().getPosition();
		}

	}
	m_moveThisFrame = false;
	m_startOfInput = false;
	for (auto& e : entities)
	{
		Entity &tempE = *e.get();
		for (auto& f : entities)
		{
			int xVal, yVal, wVal, hVal;
			xVal = (playerPos.X() - 120);
			yVal = (playerPos.Y() - 120);
			wVal = (playerPos.X() + 240);
			hVal = (playerPos.Y() + 240);
			if (xVal < 0)
			{
				xVal = 0;
			}
			if (yVal < 0)
			{
				yVal = 0;
			}
			if (wVal > 3840)
			{
				wVal = 3840;
			}
			if (hVal > 1800)
			{
				hVal = 1800;
			}
			
			Entity& tempF = *f.get();
			if (xVal + 360 > tempF.getComponent<PositionComponent>().getPosition().x && xVal < tempF.getComponent<PositionComponent>().getPosition().x + 360 &&
				yVal + 360 > tempF.getComponent<PositionComponent>().getPosition().y && yVal < tempF.getComponent<PositionComponent>().getPosition().y + tempF.getComponent<PositionComponent>().getPosition().x)
			{

				if (tempE.getComponent<BotComponent>().getBotMode())
				{
					tempE.getComponent<BotComponent>().setFakeStickX(fakeStickXVal);
				}
				if (tempE.getComponentString() == "player" && tempE.getComponent<PositionComponent>().getPosition() != Vector2(230000, 20000) &&
					tempE.getComponent<SpriteComponent>().getCurrentState() == PlayerStates::IdlePlayer)
				{
					if (stick.Y() == 1)
					{
						handleMove(tempE, m_down.execute());
					}
					else if (stick.X() == 1 || (tempE.getComponent<BotComponent>().getBotMode() && tempE.getComponent<BotComponent>().getFakeStickX() == 1))
					{
						handleMove(tempE, m_right.execute());
					}
					else if (stick.X() == -1 || (tempE.getComponent<BotComponent>().getBotMode() && tempE.getComponent<BotComponent>().getFakeStickX() == -1))
					{
						handleMove(tempE, m_left.execute());
					}
					else if (stick.Y() == -1)
					{
						handleMove(tempE, m_up.execute());
					}
					handleBoundary(tempE, t_mapsize.at(0), t_mapsize.at(1));

				}
				if (SDL_JoystickGetButton(stick.getStick(), 4) != 0)
				{
					int tempEnumX = tempE.getComponent<PositionComponent>().getPreviousPosition().X();
					int tempEnumY = tempE.getComponent<PositionComponent>().getPreviousPosition().Y();
					tempEnumX = tempEnumX % 120;
					tempEnumY = tempEnumY % 120;

					if (!tempEnumX == 0 || !tempEnumY == 0)
					{
						tempE.getComponent<PositionComponent>().popPreviousPosition();
					}
					else
					{
						tempE.getComponent<PositionComponent>().setToPreviousPos();
					}

					if (!tempE.getComponent<PositionComponent>().isEmpty())
					{
						m_moveThisFrame = true;
					}
					if (tempE.getComponentString() == "player")
					{
						tempE.getComponent<SpriteComponent>().updateState(PlayerStates::IdlePlayer);
					}

					tempE.getComponent<SpriteComponent>().setPosAndSize(tempE.getComponent<PositionComponent>().getPosition().X(),
						tempE.getComponent<PositionComponent>().getPosition().Y(),
						tempE.getComponent<BodyComponent>().getSize().X(),
						tempE.getComponent<BodyComponent>().getSize().Y());
				}
				if (tempE.getComponentString() == "stop" || tempE.getComponentString() == "move")
				{


					if (tempF.getComponentString() == "player" || (tempE.getComponentString() == "move") && tempF.getComponentString() == "move" && (tempE.getComponent<PositionComponent>().getPosition() != tempF.getComponent<PositionComponent>().getPosition()))
					{
						if (m_colSys.collides(tempE.getComponent<PositionComponent>().getPosition(),
							tempE.getComponent<BodyComponent>().getSize(),
							tempF.getComponent<PositionComponent>().getPosition(),
							tempF.getComponent<BodyComponent>().getSize()))
						{

							tempE.getComponent<SpriteComponent>().setPosAndSize(tempE.getComponent<PositionComponent>().getPosition().X(),
								tempE.getComponent<PositionComponent>().getPosition().Y(),
								tempE.getComponent<BodyComponent>().getSize().X(),
								tempE.getComponent<BodyComponent>().getSize().Y());

							tempF.getComponent<PositionComponent>().setToPreviousPos();

							tempF.getComponent<SpriteComponent>().updateState(PlayerStates::IdlePlayer);
						}
					}

				}
				if (tempE.getComponentString() == "spiky" && !SDL_JoystickGetButton(stick.getStick(), 4) != 0)
				{


					if (tempF.getComponentString() == "player")
					{
						if (m_colSys.collides(tempE.getComponent<PositionComponent>().getPosition(),
							tempE.getComponent<BodyComponent>().getSize(),
							tempF.getComponent<PositionComponent>().getPosition(),
							tempF.getComponent<BodyComponent>().getSize()))
						{
							tempE.getComponent<PositionComponent>().setPosition(Vector2(240000, 20000));
							tempE.getComponent<SpriteComponent>().setPosAndSize(tempE.getComponent<PositionComponent>().getPosition().X(),
								tempE.getComponent<PositionComponent>().getPosition().Y(),
								tempE.getComponent<BodyComponent>().getSize().X(),
								tempE.getComponent<BodyComponent>().getSize().Y());
							tempF.getComponent<SpriteComponent>().updateState(PlayerStates::DyingPlayer);
							m_diedToCactus = true;
						}
					}

				}


			}

		}
	}



	if (m_moveThisFrame)
	{
		if (newTimer < (MAX_TIME*0.5f))
		{
			newTimer *= 1.7;
		}
		timer = newTimer;
	}
	if (stick.X() != 0 || stick.Y() != 0 || SDL_JoystickGetButton(stick.getStick(), 4) != 0)
	{
		m_inputThisFrame = true;
	}
}

void EntityManager::update(int yVal, int xVal, int hVal, int wVal)
{
	Entity& tempE=*entities[0];
	Vector2 playerPos;
	for (auto& e : entities)
	{
		Entity& tempE = *e.get();
		if (tempE.getComponentString() == "player")
		{
			playerPos = tempE.getComponent<PositionComponent>().getPosition();
		}

	}
	if (timer < MAX_TIME)
		timer++;
	if (!m_inputThisFrame)
	{
		newTimer = 1;
	}
	m_inputThisFrame = false;
	for (auto& f : entities)
	{
		int xVal, yVal, wVal, hVal;
		xVal = (playerPos.X() - 120);
		yVal = (playerPos.Y()-120);
		wVal = (playerPos.X() + 240);
		hVal = (playerPos.Y() + 240);
		if (xVal < 0)
		{
			xVal = 0;
		}
		if (yVal < 0)
		{
			yVal = 0;
		}
		if (wVal > 3840)
		{
			wVal = 3840;
		}
		if (hVal > 1800)
		{
			hVal = 1800;
		}
		Entity& tempF = *f.get();
		if (xVal + 360 > tempF.getComponent<PositionComponent>().getPosition().x && xVal < tempF.getComponent<PositionComponent>().getPosition().x +360 &&
			yVal + 360 > tempF.getComponent<PositionComponent>().getPosition().y && yVal < tempF.getComponent<PositionComponent>().getPosition().y + tempF.getComponent<PositionComponent>().getPosition().x)
		{
			f->update();

		}


	}
	movement();
	pushing();
	dying();
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
		if (tempF.getComponentString() == "player" || tempF.getComponentString() == "move")
		{
			if (m_colSys.collides(t_pos,
				t_size,
				tempF.getComponent<PositionComponent>().getPosition(),
				tempF.getComponent<BodyComponent>().getSize()))
			{
				tempF.getComponent<PositionComponent>().setToPreviousPos();
				tempF.getComponent<SpriteComponent>().updateState(PlayerStates::IdlePlayer);
				Vector2 pos = tempF.getComponent<PositionComponent>().getPosition();
				Vector2 size = tempF.getComponent<BodyComponent>().getSize();
				tempF.getComponent<SpriteComponent>().setPosAndSize(pos.x, pos.y, size.x, size.y);

				fakeStickXVal *= -1;

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
	m_startOfInput = true;

	m_direction = t_str;
	t_ent.getComponent<SpriteComponent>().updateState(PlayerStates::MovingPlayer);

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


void EntityManager::movement()
{

	bool isMoving = false;
	for (auto& e : entities)
	{
		Entity& tempE = *e.get();
		if (tempE.getComponent<SpriteComponent>().getCurrentState() == PlayerStates::MovingPlayer || tempE.getComponent<SpriteComponent>().getCurrentState() == PlayerStates::PushingPlayer)
		{
			isMoving = true;
		}
	}
	for (auto& e : entities)
	{
		Entity& tempE = *e.get();
		if (isMoving)
		{
			tempE.getComponent<PositionComponent>().setPreviousPosition(tempE.getComponent<PositionComponent>().getPosition());
		}
		if (tempE.getAlive() && tempE.getComponentString() == "player" &&
			(tempE.getComponent<SpriteComponent>().getCurrentState() == PlayerStates::MovingPlayer || tempE.getComponent<SpriteComponent>().getCurrentState() == PlayerStates::PushingPlayer))
		{

			Vector2 tempVec = m_moveSys.move(tempE.getComponent<PositionComponent>().getPosition(), m_direction);
			if (tempE.getComponent<SpriteComponent>().finishedAnime())
			{
				tempVec = tempE.getComponent<PositionComponent>().getPosition();
				tempVec = Vector2((int((tempVec.x + 60) / 120)) * 120, (int((tempVec.y + 60) / 120)) * 120);
				tempE.getComponent<SpriteComponent>().updateState(PlayerStates::IdlePlayer);
			}
			tempE.getComponent<PositionComponent>().setPosition(tempVec);
			tempE.getComponent<SpriteComponent>().setPosAndSize(tempE.getComponent<PositionComponent>().getPosition().X(), tempE.getComponent<PositionComponent>().getPosition().Y(),
				tempE.getComponent<BodyComponent>().getSize().X(), tempE.getComponent<BodyComponent>().getSize().Y());
		}


		if (m_startOfInput)
		{
			Vector2 tempVec = tempE.getComponent<PositionComponent>().getPosition();
			tempE.getComponent<PositionComponent>().setPreviousPosition(Vector2((int((tempVec.x + 60) / 120)) * 120, (int((tempVec.y + 60) / 120)) * 120));
		}
	}
	m_startOfInput = false;

}

void EntityManager::pushing()
{
	for (auto& e : entities)
	{
		Entity& tempE = *e.get();
		if (tempE.getComponentString() == "move")
		{
			if (tempE.getComponent<PositionComponent>().getPosition() != Vector2(7200, 480))
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


							Vector2 tempVec = m_moveSys.move(tempE.getComponent<PositionComponent>().getPosition(), m_direction);

							tempE.getComponent<PositionComponent>().setPreviousPosition(tempE.getComponent<PositionComponent>().getPosition());
							tempE.getComponent<PositionComponent>().setPosition(tempVec);
							tempE.getComponent<SpriteComponent>().setPosAndSize(tempE.getComponent<PositionComponent>().getPosition().X(), tempE.getComponent<PositionComponent>().getPosition().Y(),
								tempE.getComponent<BodyComponent>().getSize().X(), tempE.getComponent<BodyComponent>().getSize().Y());
							tempF.getComponent<SpriteComponent>().updateState(PlayerStates::PushingPlayer);
						}
						if (tempF.getComponent<SpriteComponent>().finishedAnime())
						{
							Vector2 tempVec = tempE.getComponent<PositionComponent>().getPosition();
							tempVec = Vector2((int((tempVec.x + 60) / 120)) * 120, (int((tempVec.y + 60) / 120)) * 120);
							/*tempE.getComponent<PositionComponent>().setPosition(tempVec);
							tempE.getComponent<SpriteComponent>().setPosAndSize(tempE.getComponent<PositionComponent>().getPosition().X(), tempE.getComponent<PositionComponent>().getPosition().Y(),
								tempE.getComponent<BodyComponent>().getSize().X(), tempE.getComponent<BodyComponent>().getSize().Y());*/
						}

					}
				}
			}
			
		}
	}
}

void EntityManager::dying()
{
	for (auto& e : entities)
	{
		Entity& tempE = *e.get();
		if (tempE.getComponentString() == "player" && tempE.getComponent<SpriteComponent>().getCurrentState() == PlayerStates::DyingPlayer &&
			tempE.getComponent<SpriteComponent>().finishedAnime())
		{
			//tempE.getComponent<PositionComponent>().setPreviousPosition(tempE.getComponent<PositionComponent>().getPosition());
			tempE.getComponent<PositionComponent>().setPosition(Vector2(230000, 20000));
			tempE.getComponent<SpriteComponent>().setPosAndSize(tempE.getComponent<PositionComponent>().getPosition().X(),
				tempE.getComponent<PositionComponent>().getPosition().Y(),
				tempE.getComponent<BodyComponent>().getSize().X(),
				tempE.getComponent<BodyComponent>().getSize().Y());
			tempE.getComponent<SpriteComponent>().updateState(PlayerStates::IdlePlayer);
		}
	}
}
