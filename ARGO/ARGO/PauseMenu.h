#pragma once
#include <SDL.h>
#include "Vector2.h"
#include "Joystick.h"
class PauseMenu
{
public:
	PauseMenu();
    ~PauseMenu();
	void init();
	void input(SDL_Event& t_event, Joystick t_stick);
	void update();
	void render(SDL_Renderer*& t_renderer);
	bool anyActive();
	int getTime();
	void resetTime();
	static const int TIME_SPEED = 20;
private:
	SDL_Surface* loadedSurfaceBack;
	SDL_Surface* loadedSurfaceObj;
	SDL_Surface* loadedSurfaceAdjec;
	SDL_Surface* loadedSurfaceSelect;
	SDL_Texture* m_textureBack;
	SDL_Texture* m_textureObj;
	SDL_Texture* m_textureAdjec;
	SDL_Texture* m_textureSelect;
	SDL_Rect dstrectBack;
	SDL_Rect dstrectObjSliced;
	SDL_Rect dstrectObj;
	SDL_Rect dstrectAdjecSliced;
	SDL_Rect dstrectAdjec;
	SDL_Rect dstrectSelect;

	static const int NUM_OF_BOXES = 6;
	SDL_Rect boxRectSliced[NUM_OF_BOXES];
	SDL_Rect boxRect[NUM_OF_BOXES];
	Vector2 selectBox[NUM_OF_BOXES];
	bool boxSelected[NUM_OF_BOXES];
	SDL_Rect srcrect[NUM_OF_BOXES];

	
	int timer;
	int currentBox;
};