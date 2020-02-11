#include "BoundarySystem.h"

BoundarySystem::BoundarySystem()
{
}

BoundarySystem::~BoundarySystem()
{
}

void BoundarySystem::hitBoundary(PositionComponent t_pos, BodyComponent t_body)
{
	if (t_pos.getPosition().x <= 0 || t_pos.getPosition().x + t_body.getSize().x >= 3840 /* max screen width*/
		|| t_pos.getPosition().y <= 0 || t_pos.getPosition().y + t_body.getSize().y >= 2160 /* max screen height*/)
	{
		t_pos.setToPreviousPos();
	}
}
