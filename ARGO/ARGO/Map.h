#pragma once
#include "MapTile.h"
#include  "MapHolder.h"
class Map
{
public:
	Map();
	~Map();
	
	MapHolder m_mapHolder;
	mapTile tile[50][50];
	void init(SDL_Renderer*& t_renderer);
	void render(SDL_Renderer*& t_renderer, int i, int j);
private:
	Vector2 mapArr[50][50];
	std::string catStr, flagStr, platformStr, wallStr, yarnStr;

	void drawTile(SDL_Renderer*& t_renderer,int i,int j);
	Sprite spriteTemp;
};