#include "PauseMenu.h"

PauseMenu::PauseMenu()
{
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::init()
{
	loadedSurfaceBack = SDL_LoadBMP("ASSETS/IMAGES/pauseBack.bmp");
	loadedSurfaceObj = SDL_LoadBMP("ASSETS/IMAGES/objects.bmp");
	loadedSurfaceAdjec = SDL_LoadBMP("ASSETS/IMAGES/adjectives.bmp");
	loadedSurfaceSelect = SDL_LoadBMP("ASSETS/IMAGES/selector.bmp");

	selectBox[0] = Vector2(2650, 250);
	selectBox[1] = Vector2(3200, 250);
	selectBox[2] = Vector2(selectBox[0].X(), 800);
	selectBox[3] = Vector2(selectBox[1].X(), 800);
	selectBox[4] = Vector2(selectBox[0].X(), 1350);
	selectBox[5] = Vector2(selectBox[1].X(), 1350);
	
	for (int box = 0; box < NUM_OF_BOXES; box++)
	{
		boxSelected[box] = false;
		srcrect[box] = { 0, 0, 500, 100 };
		boxRectSliced[box] = { int(selectBox[box].X()), int(selectBox[box].Y()), 500, 100 };
		boxRect[box] = { int(selectBox[box].X()), int(selectBox[box].Y()), 500, 500 };
	}
	dstrectBack = { 2600, 100, 1150, 1800 };
	
	currentBox = 0;
	dstrectSelect = { int(selectBox[currentBox].X() - 5), int(selectBox[currentBox].Y() - 5), 510, 110 };
}

void PauseMenu::input(SDL_Event& t_event, Joystick t_stick)
{
	if (timer == TIME_SPEED)
	{
		if (SDL_JoystickGetButton(t_stick.getStick(), 0) != 0)
		{
			for (int box = 0; box < NUM_OF_BOXES; box++)
			{
				if (!boxSelected[box] && dstrectSelect.x + 5 == selectBox[box].X() && dstrectSelect.y + 5 == selectBox[box].Y())
				{
					boxSelected[box] = true;
					dstrectSelect.y += srcrect[box].y;
					timer = 0;
				}
				else if (boxSelected[box])
				{
					srcrect[box] = { 0, int(dstrectSelect.y + 5 - selectBox[box].Y()), 500, 100 };
					boxSelected[box] = false;
					dstrectSelect.y = selectBox[box].Y() - 5;
					timer = 0;
				}
			}
		}
		if (!anyActive())
		{
			if (t_stick.X() == -1 || t_stick.X() == 1)
			{
				if (currentBox % 2 == 0)
				{
					currentBox++;
					timer = 0;
				}
				else 
				{
					currentBox--;
					timer = 0;
				}
			}
			else if (t_stick.Y() == 1)
			{
				currentBox += 2;
				timer = 0;
				if (currentBox >= NUM_OF_BOXES)
				{
					currentBox -= NUM_OF_BOXES;
				}
			}
			else if (t_stick.Y() == -1)
			{
				currentBox -= 2;
				timer = 0;
				if (currentBox < 0)
				{
					currentBox += NUM_OF_BOXES;
				}
			}
			dstrectSelect = { int(selectBox[currentBox].X() - 5), int(selectBox[currentBox].Y() - 5), 510, 110 };
		}
		for (int box = 0; box < NUM_OF_BOXES; box++)
		{
			if (boxSelected[box] && dstrectSelect.x + 5 == selectBox[box].X() && dstrectSelect.y + 5 >= selectBox[box].Y() && dstrectSelect.y + 405 >= selectBox[box].Y())
			{
				if (t_stick.Y() == 1)
				{
					dstrectSelect.y += 100;
					timer = 0;
					if (dstrectSelect.y - selectBox[box].Y() > 400)
					{
						dstrectSelect.y -= 500;
					}
				}
				else if (t_stick.Y() == -1)
				{
					dstrectSelect.y -= 100;
					timer = 0;
					if (dstrectSelect.y + 5 < selectBox[box].Y())
					{
						dstrectSelect.y += 500;
					}
				}
			}
		}
	}
}

void PauseMenu::update()
{
	if (timer < TIME_SPEED)
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

	if (m_textureAdjec == NULL)
	{
		m_textureAdjec = SDL_CreateTextureFromSurface(t_renderer, loadedSurfaceAdjec);
	}

	SDL_Texture* forAllTexture;
	for (int box = 0; box < NUM_OF_BOXES; box++)
	{
		if (box % 2 == 0)
		{
			forAllTexture = m_textureObj;
		}
		else
		{
			forAllTexture = m_textureAdjec;
		}
		if (!boxSelected[box])
			SDL_RenderCopy(t_renderer, forAllTexture, &srcrect[box], &boxRectSliced[box]);
		else
			SDL_RenderCopy(t_renderer, forAllTexture, NULL, &boxRect[box]);
	}
	if (m_textureSelect == NULL)
	{
		m_textureSelect = SDL_CreateTextureFromSurface(t_renderer, loadedSurfaceSelect);
	}
	SDL_RenderCopy(t_renderer, m_textureSelect, NULL, &dstrectSelect);
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
