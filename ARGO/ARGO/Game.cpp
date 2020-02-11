#include "Game.h"
GameState Game::m_currentMode{ GameState::intro };
LevelState Game::m_currentLevel{ LevelState::Level1 };

EntityManager manager;
auto& newPlayer(manager.addEntity());

Game::Game()
{

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
	
	
	stick.init();

	newPlayer.addComponent<PositionComponent>();
	newPlayer.addComponent<SpriteComponent>();
	newPlayer.getComponent<PositionComponent>().setPosition(Vector2(500, 500));
	newPlayer.getComponent<SpriteComponent>().setPathAndScreen("ASSETS/IMAGES/bananacat.bmp", m_renderer);
	newPlayer.getComponent<SpriteComponent>().setPosAndSize(newPlayer.getComponent<PositionComponent>().getPosition().X(), newPlayer.getComponent<PositionComponent>().getPosition().Y(), 50, 50);
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
		
		std::cout << stick.X() << std::endl;
		
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
				std::cout << m_event.jaxis.value << std::endl;
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
		else if (SDL_JoystickGetButton(stick.getStick(), 0) != 0)
		{
			handleMove(newPlayer, "down");
		}
		else if (SDL_JoystickGetButton(stick.getStick(), 1) != 0)
		{
			handleMove(newPlayer, "right");
		}
		else if (SDL_JoystickGetButton(stick.getStick(), 2) != 0)
		{
			handleMove(newPlayer, "left");
		}
		else if (SDL_JoystickGetButton(stick.getStick(), 3) != 0)
		{
			handleMove(newPlayer, "up");
		}
	default:
		break;
	}
	
	if (stick.X() == -1 && keyTest)
	{
		switch (m_currentMode)
		{
		case GameState::intro://no process events for this screen
			m_currentMode = GameState::credits;
			break;
		case GameState::splash://no process events for this screen
			m_currentMode = GameState::intro;
			break;
		case GameState::mainMenu://no process events for this screen
			m_currentMode = GameState::splash;
			break;
		case GameState::gameplay://no process events for this screen
			m_currentMode = GameState::mainMenu;
			break;
		case GameState::options://no process events for this screen
			m_currentMode = GameState::gameplay;
			break;
		case GameState::credits://no process events for this screen
			m_currentMode = GameState::options;
			break;
		default:
			break;
		}
		keyTest = false;
	}
	else if (stick.X() == 1 && keyTest)
	{
		switch (m_currentMode)
		{
		case GameState::intro://no process events for this screen
			m_currentMode = GameState::splash;
			break;
		case GameState::splash://no process events for this screen
			m_currentMode = GameState::mainMenu;
			break;
		case GameState::mainMenu://no process events for this screen
			m_currentMode = GameState::gameplay;
			break;
		case GameState::gameplay://no process events for this screen
			m_currentMode = GameState::credits;
			break;
		case GameState::options://no process events for this screen
			m_currentMode = GameState::options;
			break;
		case GameState::credits://no process events for this screen
			m_currentMode = GameState::intro;
			break;
		default:
			break;
		}
		keyTest = false;
	}
}

void Game::update()
{
	static int count = 0; count++;
	manager.update();
	switch (m_currentMode)//gamestate
	{
	case GameState::intro://no process events for this screen
		m_introScr.update();
		break;
	case GameState::splash://no process events for this screen
		m_splashScr.update();
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
	case GameState::credits://no process events for this screen
		m_creditsScr.update();
		break;
	default:
		break;
	}
}

void Game::render()
{
	SDL_RenderClear(m_renderer);
	switch (m_currentMode)//gamestate
	{
	case GameState::intro://no process events for this screen
		m_introScr.render(m_renderer);
		break;
	case GameState::splash://no process events for this screen
		m_splashScr.render(m_renderer);
		break;
	case GameState::mainMenu://no process events for this screen
		m_mainMenuScr.render(m_renderer);
		break;
	case GameState::gameplay://no process events for this screen
		m_gamePlayScr.render(m_renderer);
		manager.draw(m_renderer);
		break;
	case GameState::options://no process events for this screen
		m_optionsScr.render(m_renderer);
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
	std::cout << "Game Cleaned" << std::endl;
}

void Game::handleMove(Entity &t_ent, std::string t_str)
{
	
	Vector2 tempVec = m_moveSys.move(t_ent.getComponent<PositionComponent>().getPosition(), t_str);
	t_ent.getComponent<PositionComponent>().setPosition(tempVec);
	t_ent.getComponent<SpriteComponent>().setPosAndSize(newPlayer.getComponent<PositionComponent>().getPosition().X(), newPlayer.getComponent<PositionComponent>().getPosition().Y(), 50, 50);
}
