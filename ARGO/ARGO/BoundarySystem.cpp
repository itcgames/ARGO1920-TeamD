#include "BoundarySystem.h"

BoundarySystem::BoundarySystem()
{
}

BoundarySystem::~BoundarySystem()
{
}

void BoundarySystem::hitBoundary(PositionComponent t_pos, BodyComponent t_body, Vector2 t_mapTopLeft, Vector2 t_mapBottomRight)
{
	if (t_pos.getPosition().x <= t_mapTopLeft.x || t_pos.getPosition().x + t_body.getSize().x >= t_mapBottomRight.x/* max screen width*/
		|| t_pos.getPosition().y <= t_mapTopLeft.y || t_pos.getPosition().y + t_body.getSize().y >= t_mapBottomRight.y /* max screen height*/)
	{
		t_pos.setToPreviousPos();
	}
}
