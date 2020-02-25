#include "Game.h"

GameState Game::m_currentMode{ GameState::mainMenu };
EntityManager manager;
auto& newPlayer(manager.addEntity("player"));
auto& flag(manager.addEntity("goal"));
auto& platform(manager.addEntity("stop"));
auto& cactus(manager.addEntity("spiky"));
auto& rock(manager.addEntity("move"));





Game::Game()
{

	//m_factory->createCatAudio(newPlayer, "ASSETS/AUDIO/temp.wav");

}

Game::~Game()
{

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{

	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_BORDERLESS;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		m_window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		m_renderer = SDL_CreateRenderer(m_window, -1, 0);
		if (m_renderer)
		{
			SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
		}

		isRunning = true;
	}
	
	
	m_gamePlayScr.init(m_renderer);
	Map tempMap = m_gamePlayScr.getMap();
	m_currentLevel = tempMap.getLevelNum();
	m_characterVectorArray.push_back(m_factory->initEntityCat(newPlayer, Vector2(tempMap.getPlayerPos()), Vector2(120, 120), "ASSETS/IMAGES/dance.bmp", true, "ASSETS/AUDIO/temp.wav", false, *m_renderer));
	m_characterVectorArray.push_back(m_factory->initEntityFlag(flag, Vector2(tempMap.getFlagPos()), Vector2(120, 120), "ASSETS/IMAGES/dance.bmp", true, "ASSETS/AUDIO/temp.wav", false, *m_renderer));
	m_characterVectorArray.push_back(m_factory->initEntityRock(rock, Vector2(tempMap.getClockPos()), Vector2(120, 120), "ASSETS/IMAGES/dance.bmp", true, "ASSETS/AUDIO/temp.wav", false, *m_renderer));
	m_characterVectorArray.push_back(m_factory->initEntityPlatform(platform, Vector2(tempMap.getPlatformPos()), Vector2(120, 120), "ASSETS/IMAGES/dance.bmp", true, "ASSETS/AUDIO/temp.wav", false, *m_renderer));
	m_characterVectorArray.push_back(m_factory->initEntityCactus(cactus, Vector2(tempMap.getcactusPos()), Vector2(120, 120), "ASSETS/IMAGES/dance.bmp", true, "ASSETS/AUDIO/temp.wav", false, *m_renderer));
	/*initEnts(newPlayer, Vector2(tempMap.getPlayerPos()), Vector2(120, 120), "ASSETS/IMAGES/dance.bmp", true, "ASSETS/AUDIO/temp.wav", false);
	initEnts(flag, Vector2(tempMap.getRockPos()), Vector2(120, 120), "ASSETS/IMAGES/flag.bmp", true, "ASSETS/AUDIO/temp.wav", false);
	initEnts(rock, Vector2(tempMap.getFlagPos()), Vector2(120, 120), "ASSETS/IMAGES/yarn.bmp", true, "ASSETS/AUDIO/temp.wav", false);
	initEnts(platform, Vector2(tempMap.getPlatformPos()), Vector2(120, 120), "ASSETS/IMAGES/platform.bmp", true, "ASSETS/AUDIO/temp.wav", false);
	initEnts(cactus, Vector2(tempMap.getcactusPos()), Vector2(120, 120), "ASSETS/IMAGES/cactus.bmp", true, "ASSETS/AUDIO/temp.wav", false);*/

	m_currentLevel = 0;// tempMap.getLevelNum();
	


	lastString = "ASSETS/IMAGES/states.bmp";
	Entity* arr[]{ &newPlayer,&flag,&platform,&cactus,&rock };

	std::copy(std::begin(arr), std::end(arr), std::begin(entArr));
	stick.init();

	
	flag.addComponent<AudioComponent>().playAudio();
	flag.addComponent<AudioComponent>().closeAudio();

	answer = m_gamePlayScr.getChanges();
	answer2 = answer;
	
}

void Game::handleEvents()
{
	SDL_PollEvent(&m_event);
	switch (m_event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_JOYAXISMOTION:
		if (m_event.jaxis.which == 0)
		{
			if (m_event.jaxis.axis == 0)
			{
				if (m_event.jaxis.value < -20000)
				{

					stick.setX(-1);
				}
				else if (m_event.jaxis.value > 20000)
				{
					stick.setX(1);

				}
				else {
					stick.setX(0);
					keyTest = true;
				}
			}
			if (m_event.jaxis.axis == 1)
			{
				if (m_event.jaxis.value < -stick.getDeadZone())
				{
					stick.setY(-1);
				}
				else if (m_event.jaxis.value > stick.getDeadZone())
				{
					stick.setY(1);
				}
				else {
					stick.setY(0);
				}
			}
		}
		break;
	case SDL_JOYBUTTONDOWN:
		if (SDL_JoystickGetButton(stick.getStick(), 5) != 0)
		{
			isRunning = false;
		}
		break;
	}
	
	switch (m_currentMode)//gamestate
	{
	case GameState::splash:
		break;
	case GameState::licence:
		m_licence.handleEvents(m_event, m_currentMode);
		break;
	case GameState::mainMenu:
		m_mainMenuScr.handleEvents(m_event, m_currentMode, stick);
		break;
	//case GameState::gameplay://no process events for this screen
	//	if ((m_event.type == SDL_JOYBUTTONDOWN || m_event.type == SDL_JOYAXISMOTION) && !m_gamePlayScr.isPaused())
	//	{
	//		manager.handleEvents(stick, m_gamePlayScr.getMapCorners());
	//	}
	//	m_gamePlayScr.handleEvents(m_event, m_currentMode, stick);
	//	break;
	case GameState::options:
		m_optionsScr.handleEvents(m_event, m_currentMode, stick);
		break;
	case GameState::help:
		m_helpScr.handleEvents(m_event, m_currentMode, stick);
	case GameState::credits:
		break;
	default:
		break;
	}
}

void Game::update()
{
	//newPlayer.destroy();
	//flag.destroy();

	//manager.refresh();
	answer = m_gamePlayScr.getChanges();


	newPlayer.setComponentString(answer[1]);
	rock.setComponentString(answer[3]);
	platform.setComponentString(answer[5]);
	flag.setComponentString(answer[7]);
	cactus.setComponentString(answer[9]);

	if (m_gamePlayScr.getCurrentLevel() -1 > m_optionsScr.getAchievementCount())
	{
		m_optionsScr.increaseAchievementCount(m_renderer);
	}
	//updateEnts(bot, Vector2(bot.getComponent<PositionComponent>().getPosition().X(), bot.getComponent<PositionComponent>().getPosition().Y()), Vector2(120, 120), "ASSETS/IMAGES/bot.bmp", true);
	m_optionsScr.setCatHurtAchievement(manager.GetDeathToCactus());
	m_optionsScr.setCatStateAchievement(m_gamePlayScr.getSwappedStates());
	Map tempMap = m_gamePlayScr.getMap();
	for (int i = 0, j = 0; i < 5; i++, j += 2)
	{
		if (entArr[i] != NULL)
		{
			if (answer[j] == "cat")
			{				
				if (stick.X()==1)
				{
					lastString = "ASSETS/IMAGES/states.bmp";
				}
				else if (stick.X() == -1)
				{
					lastString = "ASSETS/IMAGES/states2.bmp";
				}
				if (m_currentLevel != tempMap.getLevelNum())
					entArr[i]->getComponent<PositionComponent>().setPosition(tempMap.getPlayerPos());
			updateEnts(*entArr[i], Vector2(entArr[i]->getComponent<PositionComponent>().getPosition().X(), entArr[i]->getComponent<PositionComponent>().getPosition().Y()), Vector2(120, 120), lastString, true, false);
			}
			else if (answer[j] == "flag")
			{
				if (m_currentLevel != tempMap.getLevelNum())
					entArr[i]->getComponent<PositionComponent>().setPosition(tempMap.getFlagPos());
				updateEnts(*entArr[i], Vector2(entArr[i]->getComponent<PositionComponent>().getPosition().X(), entArr[i]->getComponent<PositionComponent>().getPosition().Y()), Vector2(120, 120), "ASSETS/IMAGES/flag.bmp", true, false);
			}
			else if (answer[j] == "cactus")
			{
				if (m_currentLevel != tempMap.getLevelNum())
					entArr[i]->getComponent<PositionComponent>().setPosition(tempMap.getcactusPos());
				updateEnts(*entArr[i], Vector2(entArr[i]->getComponent<PositionComponent>().getPosition().X(), entArr[i]->getComponent<PositionComponent>().getPosition().Y()), Vector2(120, 120), "ASSETS/IMAGES/cactus.bmp", true, false);
			}
			else if (answer[j] == "clock")
			{
				if (m_currentLevel != tempMap.getLevelNum())
					entArr[i]->getComponent<PositionComponent>().setPosition(tempMap.getClockPos());
				updateEnts(*entArr[i], Vector2(entArr[i]->getComponent<PositionComponent>().getPosition().X(), entArr[i]->getComponent<PositionComponent>().getPosition().Y()), Vector2(120, 120), "ASSETS/IMAGES/clock.bmp", true,false);
			}
			else if (answer[j] == "platform")
			{
				if (m_currentLevel != tempMap.getLevelNum())
					entArr[i]->getComponent<PositionComponent>().setPosition(tempMap.getPlatformPos());
				updateEnts(*entArr[i], Vector2(entArr[i]->getComponent<PositionComponent>().getPosition().X(), entArr[i]->getComponent<PositionComponent>().getPosition().Y()), Vector2(120, 120), "ASSETS/IMAGES/book.bmp", true, false);
			}
			entArr[i]->setComponentString(answer[j+1]);
		}
	}
	m_currentLevel = tempMap.getLevelNum();

	switch (m_currentMode)//gamestate
	{
	case GameState::intro:
		m_intro.update(m_currentMode);
		break;
	case GameState::splash://no process events for this screen
		m_splashScr.update(m_currentMode);
		break;
	case GameState::licence:
		m_licence.update(m_currentMode);
		break;
	case GameState::mainMenu://no process events for this screen
		m_mainMenuScr.update();
		break;
	case GameState::gameplay://no process events for this screen
		m_gamePlayScr.update();
		break;
	case GameState::options://no process events for this screen
		m_optionsScr.update();
		break;
	case GameState::help:
		m_helpScr.update();
		break;
	case GameState::credits://no process events for this screen
		m_creditsScr.update();
		break;
	default:
		break;
	}
	
}

void Game::subSystemUpdate()
{
	switch (m_currentMode)//gamestate
	{
	
	case GameState::gameplay://no process events for this screen
		if ((m_event.type == SDL_JOYBUTTONDOWN || m_event.type == SDL_JOYAXISMOTION))
		{
			manager.handleEvents(stick, m_gamePlayScr.getMapCorners());
		}
		m_gamePlayScr.handleEvents(m_event, m_currentMode, stick);
		break;
	default:
		break;
	}
	manager.update();
	m_gamePlayScr.fixedUpdate(manager);
}

void Game::render()
{
	SDL_RenderClear(m_renderer);
	switch (m_currentMode)//gamestate
	{
	case GameState::intro:
		m_intro.render(m_renderer);
		break;
	case GameState::licence://no process events for this screen
		m_licence.render(m_renderer);
		break;
	case GameState::splash://no process events for this screen
		m_splashScr.render(m_renderer);
		break;
	case GameState::mainMenu://no process events for this screen
		m_mainMenuScr.render(m_renderer);
		break;
	case GameState::gameplay://no process events for this screen
		m_gamePlayScr.render(m_renderer, manager);
		manager.draw(m_renderer);
		break;
	case GameState::options://no process events for this screen
		m_optionsScr.render(m_renderer);
		break;
	case GameState::help:
		m_helpScr.render(m_renderer);
		break;
	case GameState::credits://no process events for this screen
		m_creditsScr.render(m_renderer);
		break;
	default:
		break;
	}

	SDL_RenderPresent(m_renderer);
}


void Game::clean()
{
	stick.close();
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}




void Game::initEnts(Entity &t_ent,Vector2 t_pos,Vector2 t_size, std::string t_str, bool t_isAnim, const char* t_audioStr,bool t_botMode)


{
	t_ent.addComponent<BotComponent>();
	t_ent.getComponent<BotComponent>().setBotMode(t_botMode);
	t_ent.addComponent<PositionComponent>();
	t_ent.addComponent<BodyComponent>();
	t_ent.addComponent<SpriteComponent>();
	t_ent.addComponent<AudioComponent>();
	t_ent.getComponent<PositionComponent>().setPosition(t_pos);
	t_ent.getComponent<BodyComponent>().setSize(t_size);
	t_ent.getComponent< SpriteComponent>().setPathAndScreen(t_str, m_renderer, t_isAnim);
	t_ent.getComponent< SpriteComponent>().setPosAndSize(t_ent.getComponent<PositionComponent>().getPosition().X(), t_ent.getComponent<PositionComponent>().getPosition().Y(),
	t_ent.getComponent<BodyComponent>().getSize().X(), t_ent.getComponent<BodyComponent>().getSize().Y());
	t_ent.getComponent<AudioComponent>().LoadMusicFile(t_audioStr);

}

void Game::updateEnts(Entity& t_ent, Vector2 t_pos, Vector2 t_size, std::string t_str, bool t_isAnim,bool t_botMode)
{
	//t_ent.deleteComp<SpriteComponent>(&t_ent.getComponent<SpriteComponent>());
	t_ent.getComponent<BotComponent>().setBotMode(t_botMode);
	t_ent.getComponent<SpriteComponent>().resetSprite();
	t_ent.getComponent<PositionComponent>().setPosition(t_pos);
	t_ent.getComponent<BodyComponent>().setSize(t_size);
	t_ent.getComponent< SpriteComponent>().setPathAndScreen(t_str, m_renderer, t_isAnim);
	t_ent.getComponent< SpriteComponent>().setPosAndSize(t_ent.getComponent<PositionComponent>().getPosition().X(), t_ent.getComponent<PositionComponent>().getPosition().Y(),
	t_ent.getComponent<BodyComponent>().getSize().X(), t_ent.getComponent<BodyComponent>().getSize().Y());

}
