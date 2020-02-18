#ifndef FACTORYMANAGER
#define FACTORYMANAGER
#include "Factory.h"

class FactoryManager: public Factory
{
public:
	FactoryManager();
	~FactoryManager();
	void setPos(Vector2 &t_vec, int t_i, int t_j);
	void drawTile(SDL_Renderer*& t_renderer, int i, int j);
private:
	mapTile tile[18][32];
};
#endif	//!FACTORYMANAGER