#ifndef TILEHOLDER
#define TILEHOLDER
#include "Vector2.h"
#include <SDL.h>
//#include "MapTile.h"

class TileHolder
{
public:
	TileHolder() {}
	virtual ~TileHolder() {}
	virtual void setPos(Vector2 t_vec) = 0;
private:

};
#endif	//!TILEHOLDER
