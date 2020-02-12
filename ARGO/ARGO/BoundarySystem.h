#ifndef BOUNDARYSYSTEM
#define BOUNDARYSYSTEM

#include "PositionComponent.h"
#include "BodyComponent.h"
class BoundarySystem
{

public:
	BoundarySystem();
	~BoundarySystem();
	void hitBoundary(PositionComponent t_pos, BodyComponent t_body, Vector2 t_mapTopLeft, Vector2 t_mapBottomRight);
private:

};
#endif // !BOUNDARYSYSTEM
