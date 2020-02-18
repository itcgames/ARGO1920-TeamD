#ifndef FACTORY
#define FACTORY
#include "MapTile.h"
#include <SDL.h>
#include "vector2.h"
class Factory
{
	
public:
	Factory();
	~Factory();
	virtual void setPos(Vector2 &t_vec, int t_i, int t_j) = 0;
	virtual void drawTile(SDL_Renderer*& t_renderer, int i, int j) = 0;
private:
};
#endif //!FACTORY
