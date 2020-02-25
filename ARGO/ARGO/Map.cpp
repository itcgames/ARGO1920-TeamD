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
	platformStr = "ASSETS/IMAGES/platform.bmp";
	wallStr = "ASSETS/IMAGES/Wall.bmp";

	std::string line;
	std::ifstream myfile("ASSETS/MAP/level" + std::to_string(levelNum) + ".txt");
	std::vector<int> mapArray;
	if (myfile.is_open())
	{
		while (getline(myfile, line, ',') && line!="end")
		{
			mapArray.push_back(std::stoi(line));
		}
		myfile.close();
	}
	//7,6,5,2,0
		 int arrayIndex = 0;
	for (int j = 0; j < 15; j++)
	{
		for (int i = 0; i < 32; i++)
		{
			tile[i][j].setPos(Vector2(0, 0));
			if (mapArray[arrayIndex] == 14) {
				m_mapHolder.mapDoubleArray[i][j] = mapArray[arrayIndex];
				tile[i][j].init(wallStr, t_renderer);
				tile[i][j].setPos(Vector2(0 + (120 * i), 0 + (120 * j)));
			}
			else if (mapArray[arrayIndex] == 13) {
				m_mapHolder.mapDoubleArray[i][j] = mapArray[arrayIndex];
				tile[i][j].init(platformStr, t_renderer);
				tile[i][j].setPos(Vector2(0 + (120 * i), 0 + (120 * j)));
			}

			//19, 16, 17, 18, 20,
			//16=cactus 17=flag 18=platform 19=cat 20 = clock
			//cactus 16, cat 19, flag 17, clock 20, shelf 18 
			else if (mapArray[arrayIndex] == 16)
			{
				cactusPos = Vector2(0 + (120 * i), 0 + (120 * j));
			}
			else if (mapArray[arrayIndex] == 17)
			{
				flagPos = Vector2(0 + (120 * i), 0 + (120 * j));
			}
			else if (mapArray[arrayIndex] == 18)
			{
				platformPos = Vector2(0 + (120 * i), 0 + (120 * j));
			}
			else if (mapArray[arrayIndex] == 19)
			{
				catPos = Vector2(0 + (120 * i), 0 + (120 * j));
			}
			else if (mapArray[arrayIndex] == 20)
			{
				clockPos = Vector2(0 + (120 * i), 0 + (120 * j));
			}
			else {
				m_mapHolder.mapDoubleArray[i][j] = 0;

			}
			arrayIndex++;


		}
	}
	drawVectors = true;
	setAdjacents();
}

void Map::drawTile(SDL_Renderer*& t_renderer, int i, int j)
{
	tile[i][j].m_tile.render();
	if (drawVectors)
	{
		tile[i][j].renderVector(t_renderer);
	}
}

void Map::BFS(Vector2 goalPos)
{
	int x = goalPos.X(); int y = goalPos.Y();
	mapTile* goal = &tile[x][y];

	bool goalReached = false;

	std::list<mapTile*> queue;

	for (auto& t : tile)
	{
		t->setStart(false);
		t->setGoal(false);
		t->setPath(false);
		t->setVisited(false);
		t->setCost(0);
	}

	goal->setGoal(true);
	goal->setVisited(true);
	queue.push_back(goal);

	while (!queue.empty())
	{
		int originCost = queue.front()->getCost();

		for (auto& e : queue.front()->getAdjacent())
		{
			if (e->getVisited() == false)
			{
				e->setVisited(true);
				if (e->getWall() == false)
				{
					e->setCost(originCost + 1);
					e->setPreviousTile(*queue.front());
					queue.push_back(e);
				}
			}
		}
		queue.pop_front();
	}
	for (auto& t : tile)
	{
		if (t->getPrevious() && t->getWall() == false)
		{
			t->setEnd(t->getPrevious()->getCenter());
		}
	}


}

void Map::ToggleDrawVector()
{
	if (drawVectors)
	{
		drawVectors = false;
	}
	else
	{
		drawVectors = true;
	}
}

void Map::render(SDL_Renderer*& t_renderer, int i, int j)
{
	if (m_mapHolder.mapDoubleArray[i][j] == 11 ||
		m_mapHolder.mapDoubleArray[i][j] == 12||
		m_mapHolder.mapDoubleArray[i][j] == 13||
		m_mapHolder.mapDoubleArray[i][j] == 14 ||
		m_mapHolder.mapDoubleArray[i][j] == 15)
	{
		drawTile(t_renderer, i, j);
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
	Vector2 bottomRight(0 + (120 * 31), 0 + (120 * 14));
	corners.push_back(topLeft);
	corners.push_back(bottomRight);
	return corners;
}

int Map::getLevelNum()
{
	return levelNum;
}

void Map::setLevelNum(int t_level)
{
	levelNum = t_level;
}

void Map::setAdjacents()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			if (i > 0)
			{
				tile[i][j].addEdge(tile[i - 1][j]);
			}

			if (i + 1 < 15)
			{
				tile[i][j].addEdge(tile[i + 1][j]);
			}

			if (j > 0)
			{
				tile[i][j].addEdge(tile[i][j - 1]);
			}

			if (j < 32)
			{
				tile[i][j].addEdge(tile[i][j + 1]);
			}
		}
	}
}
