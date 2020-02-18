#pragma once
#include "MapTile.h"
#include "MapHolder.h"
#include <SDL.h>
#include "FactoryManager.h"
class Map
{
public:
	Map();
	~Map();
	Factory* m_factory = new FactoryManager();
	MapHolder m_mapHolder;
	mapTile tile[32][18];
	void init(SDL_Renderer*& t_renderer, int t_levelNum = 1);
	void render(SDL_Renderer*& t_renderer, int i, int j);
	std::vector<Vector2> getMapCorners();
	int getLevelNum();
private:
	Vector2 test = Vector2{ 0,0 };
	Vector2 mapArr[32][18];
	std::string catStr, flagStr, platformStr, wallStr, yarnStr;
	int levelNum;
	void drawTile(SDL_Renderer*& t_renderer,int i,int j);
};