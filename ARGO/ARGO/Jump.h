#pragma once
#include"Command.h"
#include"Joystick.h"
#include"EntityManager.h"

class JumpCommand : public Command
{
public:
	virtual void execute(Joystick& stick, std::vector<Vector2> t_mapsize, EntityManager manager);
};
