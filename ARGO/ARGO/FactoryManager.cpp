#include "FactoryManager.h"

FactoryManager::FactoryManager()
{
}

FactoryManager::~FactoryManager()
{
}

void FactoryManager::setPos(Vector2 &t_vec, int t_i, int t_j)
{
	tile[t_i][t_j].setPos(t_vec);
}

void FactoryManager::drawTile(SDL_Renderer*& t_renderer, int i, int j)
{
	tile[i][j].m_tile.render();
}
