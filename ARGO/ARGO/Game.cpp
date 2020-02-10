#include "Game.h"
GameState Game::m_currentMode{ GameState::intro };
LevelState Game::m_currentLevel{ LevelState::Level1 };

EntityManager manager;
auto& newPlayer(manager.addEntity());
auto& flag(manager.addEntity());

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
	spriteTemp.setPath("ASSETS/IMAGES/bananaCat.bmp");
	spriteTemp.setSize(150,150);

	newPlayer.addComponent<PositionComponent>();
	flag.addComponent<PositionComponent>();
	flag.getComponent<PositionComponent>().setPosition(Vector2(500, 500));
}

void Game::handleEvents()
{
	SDL_PollEvent(&m_event);
	switch (m_event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (!keyTest)
		{
			keyTest = true;
			if (m_event.key.keysym.sym == SDLK_ESCAPE)
			{
				isRunning = false;

			}
			if (m_event.key.keysym.sym == SDLK_LEFT)
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
			}
		}

		break;
	case SDL_KEYUP:
		keyTest = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	static int count = 0; count++;
	manager.update();

	std::cout << "Flag: " << flag.getComponent<PositionComponent>().getPosition().x << ", " << flag.getComponent<PositionComponent>().getPosition().y << std::endl;

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
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}
