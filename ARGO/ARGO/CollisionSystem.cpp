#include "CollisionSystem.h"

CollisionSystem::CollisionSystem()
{
	m_isColliding = false;
}

CollisionSystem::~CollisionSystem()
{
}

bool CollisionSystem::collides(PositionComponent& t_pos1, BodyComponent& t_body1, PositionComponent& t_pos2, BodyComponent& t_body2)
{
	if (t_pos1.getPosition().x + t_body1.getSize().x >= t_pos2.getPosition().x && t_pos1.getPosition().x <= t_pos2.getPosition().x + t_body2.getSize().x &&
		t_pos1.getPosition().y + t_body1.getSize().y >= t_pos2.getPosition().y && t_pos1.getPosition().y <= t_pos2.getPosition().y + t_body2.getSize().y)
	{
		// there will be an if statement here to check if an entity has a "stop" component to check if the previous position should be set for it or it should be moved
		t_pos1.setToPreviousPos();
		t_pos2.setToPreviousPos();
		m_isColliding = true;
	}
	else
	{
		m_isColliding = false;
	}
	return m_isColliding;
}


