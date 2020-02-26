#include "PauseMenu.h"
#include <fstream>
#include <sstream>
#include <iostream>
PauseMenu::PauseMenu()
{
	m_lockValue = NUM_OF_BOXES;
	m_rulesChanged = false;
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::init()
{
	loadedSurfaceBack = SDL_LoadBMP("ASSETS/IMAGES/pauseBack.bmp");
	loadedSurfaceObj = SDL_LoadBMP("ASSETS/IMAGES/objects.bmp");
	loadedSurfaceAdjecUnlock = SDL_LoadBMP("ASSETS/IMAGES/adjectivesUnlocked.bmp");
	loadedSurfaceAdjecLock = SDL_LoadBMP("ASSETS/IMAGES/adjectivesLocked.bmp");
	loadedSurfaceSelect = SDL_LoadBMP("ASSETS/IMAGES/selector.bmp");
	loadedSurfaceSelect2 = SDL_LoadBMP("ASSETS/IMAGES/selected.bmp");

	selectBox[0] = Vector2(240, 1900);
	selectBox[1] = Vector2(480, 1900);
	selectBox[2] = Vector2(960,selectBox[0].Y());
	selectBox[3] = Vector2(1200,selectBox[1].Y());
	selectBox[4] = Vector2(1680,selectBox[0].Y());
	selectBox[5] = Vector2(1920, selectBox[1].Y());
	selectBox[6] = Vector2(2400, selectBox[0].Y());
	selectBox[7] = Vector2(2640, selectBox[1].Y());
	selectBox[8] = Vector2(3120, selectBox[0].Y());
	selectBox[9] = Vector2(3360, selectBox[1].Y());
	
	for (int box = 0; box < NUM_OF_BOXES; box++)
	{
		boxSelected[box] = false;
		if(box%2==0)
			srcrect[box] = { 0, srcrect[box].y, 120, 120 };
		else
			srcrect[box] = { 0, srcrect[box].y, 240, 120 };
		boxRectSliced[box] = { int(selectBox[box].X()), int(selectBox[box].Y()), srcrect[box].w, 120 };
	}
	dstrectBack = { 0, 1800, 3840, 360 };
	
	currentBox = 1;
	m_slectOffset = Vector2(5, 5);
	dstrectSelect = { int(selectBox[currentBox].X() - m_slectOffset.x), int(selectBox[currentBox].Y() - m_slectOffset.y), 250, 170 };
	dstrectSelect2 = { int(selectBox[currentBox].X()- (m_slectOffset.x/2)), int(selectBox[currentBox].Y()- (m_slectOffset.y / 2)), 244, 124 };
}

void PauseMenu::input(SDL_Event& t_event, Joystick t_stick)
{
	if (timer == MAX_TIME)
	{
		if (SDL_JoystickGetButton(t_stick.getStick(), 0) != 0)
		{
			for (int box = 0; box < NUM_OF_BOXES; box++)
			{
				if (!anyActive() && dstrectSelect.x + m_slectOffset.x == selectBox[box].X() && dstrectSelect.y + m_slectOffset.y == selectBox[box].Y())
				{
					boxSelected[box] = true;
					currentBox += 2;
					timer = 0;
					if (currentBox >= m_lockValue)
					{
						currentBox -= m_lockValue;
					}
				}
				else if (dstrectSelect.x + m_slectOffset.x == selectBox[box].X() && dstrectSelect.y + m_slectOffset.y == selectBox[box].Y())
				{
					if (boxSelected[box])
					{
						boxSelected[box] = false;
					}
					else
					{
						for (int box2 = 1; box2 < NUM_OF_BOXES; box2 += 2)
						{
							if (boxSelected[box2])
							{
								float tempCut = srcrect[box2].y;
								srcrect[box2].y = srcrect[box].y;
								srcrect[box].y = tempCut;
								boxSelected[box2] = false;
								m_swappedStates = true;
								m_rulesChanged = true;
							}
						}
					}
					timer = 0;
				}
			}
		}
		
		if (SDL_JoystickGetHat(t_stick.getStick(), 0) == SDL_HAT_RIGHT)
		{
			currentBox += 2;
			timer = 0;
			if (currentBox >= m_lockValue)
			{
				currentBox -= m_lockValue;
			}
			if (boxSelected[currentBox])
			{
				currentBox += 2;
			}
			if (currentBox >= m_lockValue)
			{
				currentBox -= m_lockValue;
			}
		}
		else if (SDL_JoystickGetHat(t_stick.getStick(), 0) == SDL_HAT_LEFT)
		{
			currentBox -= 2;
			timer = 0;
			if (currentBox < 0)
			{
				currentBox += m_lockValue;
			}
			if (boxSelected[currentBox])
			{
				currentBox -= 2;
			}
			if (currentBox < 0)
			{
				currentBox += m_lockValue;
			}
		}
		dstrectSelect = { int(selectBox[currentBox].X() - m_slectOffset.x), int(selectBox[currentBox].Y() - m_slectOffset.y), dstrectSelect.w, dstrectSelect.h };
		if (!anyActive())
		{
			dstrectSelect2 = { int(selectBox[currentBox].X() - (m_slectOffset.x / 2)), int(selectBox[currentBox].Y() - (m_slectOffset.x / 2)), dstrectSelect2.w, dstrectSelect2.h };
		}
		
	}
}

void PauseMenu::update()
{
	if (timer < MAX_TIME)
	{
		timer++;
	}
}

void PauseMenu::render(SDL_Renderer*& t_renderer)
{
	if (m_textureBack == NULL)
	{
		m_textureBack = SDL_CreateTextureFromSurface(t_renderer, loadedSurfaceBack);
	}
	SDL_RenderCopy(t_renderer, m_textureBack, NULL, &dstrectBack);

	if (m_textureObj == NULL)
	{
		m_textureObj = SDL_CreateTextureFromSurface(t_renderer, loadedSurfaceObj);
	}

	if (m_textureAdjecUnlock == NULL)
	{
		m_textureAdjecUnlock = SDL_CreateTextureFromSurface(t_renderer, loadedSurfaceAdjecUnlock);
	}
	if (m_textureAdjecLock == NULL)
	{
		m_textureAdjecLock = SDL_CreateTextureFromSurface(t_renderer, loadedSurfaceAdjecLock);
	}

	SDL_Texture* forAllTexture;
	for (int box = NUM_OF_BOXES-1; box >= 0; box--)
	{
		if (box % 2 == 0)
		{
			forAllTexture = m_textureObj;
		}
		else if (box < m_lockValue)
		{
			forAllTexture = m_textureAdjecUnlock;
		}
		else
		{
			forAllTexture = m_textureAdjecLock;
		}
		SDL_RenderCopy(t_renderer, forAllTexture, &srcrect[box], &boxRectSliced[box]);
	}
	if (m_textureSelect == NULL)
	{
		m_textureSelect = SDL_CreateTextureFromSurface(t_renderer, loadedSurfaceSelect);
	}
	if (m_textureSelect2 == NULL)
	{
		m_textureSelect2 = SDL_CreateTextureFromSurface(t_renderer, loadedSurfaceSelect2);
	}
	SDL_RenderCopy(t_renderer, m_textureSelect, NULL, &dstrectSelect);
	if (anyActive())
	{
		SDL_RenderCopy(t_renderer, m_textureSelect2, NULL, &dstrectSelect2);	
	}
}

bool PauseMenu::anyActive()
{
	bool isAnyActive = false;
	for (int box = 0; box < NUM_OF_BOXES&& !isAnyActive; box++)
	{
		if (boxSelected[box])
		{
			isAnyActive = true;
		}
	}
	return isAnyActive;
}

int PauseMenu::getTime()
{
	return timer;
}

void PauseMenu::resetTime()
{
	timer = 0;
}

std::vector<std::string> PauseMenu::getChanges()
{
	std::vector<std::string> rules;
	for (int box = 0; box < NUM_OF_BOXES; box += 2)
	{
		if (srcrect[box].y == 0)
		{
			rules.push_back("cat");
		}
		else if (srcrect[box].y == 120)
		{
			rules.push_back("clock");
		}
		else if(srcrect[box].y == 240)
		{
			rules.push_back("platform");
		}
		else if (srcrect[box].y == 360)
		{
			rules.push_back("flag");
		}
		else
		{
			rules.push_back("cactus");
		}
		if (srcrect[box + 1].y == 0)
		{
			rules.push_back("player");
		}
		else if (srcrect[box + 1].y == 120)
		{
			rules.push_back("goal");
		}
		else if (srcrect[box + 1].y == 240)
		{
			rules.push_back("stop");
		}
		else if (srcrect[box + 1].y == 360)
		{
			rules.push_back("move");
		}
		else
		{
			rules.push_back("spiky");
		}
	}

	return rules;
}

void PauseMenu::setRules(int t_levelNum)
{
	std::ifstream myfile("ASSETS/MAP/level" + std::to_string(t_levelNum) + ".txt");
	std::string currentText = "";
	getline(myfile, currentText, ':');
	int currentBox = 0;
	while (getline(myfile, currentText, '-'))
	{
		setUIRules(currentBox, currentText);
		if (currentText == "lock")
		{
			m_lockValue = currentBox;
			currentBox -= 2;
		}
		currentBox++;
		getline(myfile, currentText, ',');
		setUIRules(currentBox, currentText);
		currentBox++;
	}
}

void PauseMenu::setUIRules(int t_index, std::string t_type)
{
	if (t_type == "cat" || t_type == "player")
		srcrect[t_index].y = 0;
	else if (t_type == "clock" || t_type == "goal")
		srcrect[t_index].y = 120;
	else if (t_type == "platform" || t_type == "stop")
		srcrect[t_index].y = 240;
	else if (t_type == "flag" || t_type == "move")
		srcrect[t_index].y = 360;
	else if (t_type == "cactus" || t_type == "spiky")
		srcrect[t_index].y = 480;
}
