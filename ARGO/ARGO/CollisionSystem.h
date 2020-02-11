#ifndef COLLISIONSYSTEM
#define COLLISIONSYSTEM
#include "PositionComponent.h"
#include "BodyComponent.h"
class CollisionSystem
{

public:
	CollisionSystem();
	~CollisionSystem();
	bool collides(PositionComponent & t_pos1, BodyComponent& t_body1, PositionComponent & t_pos2, BodyComponent & t_body2);
private:
	bool m_isColliding;
};
#endif	// !COLLISIONSYSTEM

