#include "Map.h"

#include <string>
#include <fstream>
Map::Map()
{
	levelNum = 1;
}

Map::~Map()
{
}
void Map::init(SDL_Renderer*& t_renderer, int t_levelNum)
{
	if (t_levelNum < 3)
	{
		levelNum = t_levelNum;
	}
	catStr = "ASSETS/IMAGES/bananaCat.bmp";
	flagStr = "ASSETS/IMAGES/flag.bmp";
	platformStr = "ASSETS/IMAGES/platform.bmp";
	wallStr = "ASSETS/IMAGES/Wall.bmp";
	yarnStr = "ASSETS/IMAGES/yarn.bmp";

	std::string line;
	std::ifstream myfile("ASSETS/MAP/level" + std::to_string(levelNum) + ".txt");
	std::vector<int> mapArray;
	if (myfile.is_open())
	{
		while (getline(myfile, line, ','))
		{
			mapArray.push_back(std::stoi(line));
		}
		myfile.close();
	}
	//7,6,5,2,0
		 int arrayIndex = 0;
	for (int j = 0; j < 18; j++)
	{
		for (int i = 0; i < 32; i++)
		{
			
			m_factory->setPos(test, i, j);
			//tile[i][j].setPos(Vector2(0, 0));
			if (mapArray[arrayIndex] == 14) {
				m_mapHolder.mapDoubleArray[i][j] = mapArray[arrayIndex];
				tile[i][j].init(wallStr, t_renderer);
				//tile[i][j].setPos(Vector2(0 + (120 * i), 0 + (120 * j)));
				//m_factory->setPos(Vector2(0 + (120 * i), 0 + (120 * j)), i, j);
			}
			else if (mapArray[arrayIndex] == 13) {
				m_mapHolder.mapDoubleArray[i][j] = mapArray[arrayIndex];
				tile[i][j].init(platformStr, t_renderer);
				//tile[i][j].setPos(Vector2(0 + (120 * i), 0 + (120 * j)));
				//m_factory->setPos(Vector2(0 + (120 * i), 0 + (120 * j)), i, j);
			}
			else if (mapArray[arrayIndex] == 15) {
				m_mapHolder.mapDoubleArray[i][j] = mapArray[arrayIndex];
				tile[i][j].init(yarnStr, t_renderer);
				//tile[i][j].setPos(Vector2(0 + (120 * i), 0 + (120 * j)));
				//m_factory->setPos(Vector2(0 + (120 * i), 0 + (120 * j)), i, j);
			}
			else if (mapArray[arrayIndex] == 11) {
				m_mapHolder.mapDoubleArray[i][j] = mapArray[arrayIndex];
				tile[i][j].init(catStr, t_renderer);
				//tile[i][j].setPos(Vector2(0 + (120 * i), 0 + (120 * j)));
				//m_factory->setPos(Vector2(0 + (120 * i), 0 + (120 * j)), i, j);
			}
			else if (mapArray[arrayIndex] == 12)
			{
				m_mapHolder.mapDoubleArray[i][j] = mapArray[arrayIndex];
				tile[i][j].init(flagStr, t_renderer);
				//tile[i][j].setPos(Vector2(0 + (120 * i), 0 + (120 * j)));
				//m_factory->setPos(Vector2(0 + (120 * i), 0 + (120 * j)), i, j);
			}
			else {
				m_mapHolder.mapDoubleArray[i][j] = 0;

			}
			arrayIndex++;


		}
	}
}

void Map::drawTile(SDL_Renderer*& t_renderer, int i, int j)
{
	tile[i][j].m_tile.render();
}

void Map::render(SDL_Renderer*& t_renderer, int i, int j)
{
	if (m_mapHolder.mapDoubleArray[i][j] == 11 ||
		m_mapHolder.mapDoubleArray[i][j] == 12||
		m_mapHolder.mapDoubleArray[i][j] == 13||
		m_mapHolder.mapDoubleArray[i][j] == 14 ||
		m_mapHolder.mapDoubleArray[i][j] == 15)
	{
		m_factory->drawTile(t_renderer, i, j);
		//drawTile(t_renderer, i, j);
	}
	else
	{
		//do nothing
	}
}

std::vector<Vector2> Map::getMapCorners()
{
	std::vector<Vector2> corners;
	Vector2 topLeft(0 + (120 * 1), 0 + (120 * 1));
	Vector2 bottomRight(0 + (120 * 31), 0 + (120 * 17));
	corners.push_back(topLeft);
	corners.push_back(bottomRight);
	return corners;
}

int Map::getLevelNum()
{
	return levelNum;
}
