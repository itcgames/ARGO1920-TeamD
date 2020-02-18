#pragma once
#include"EntityManager.h"
class Command
{
public:
	virtual void execute(Joystick& stick, std::vector<Vector2> t_mapsize, EntityManager manager) = 0;
};