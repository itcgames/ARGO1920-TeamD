#include "MovementSystem.h"

MovementSystem::MovementSystem()
{
}

MovementSystem::~MovementSystem()
{
}

Vector2 const MovementSystem::move(PositionComponent pos, std::string t_dir)
{
	Vector2 temp =pos.getPosition();
	if (t_dir == "up")
	{
		temp = Vector2(temp.X(), temp.Y() - 120);
	}
	else if (t_dir == "left")
	{
		temp = Vector2(temp.X()-120, temp.Y());
	}
	else if (t_dir == "right")
	{
		temp = Vector2(temp.X()+120, temp.Y());
	}
	else if (t_dir == "down")
	{
		temp = Vector2(temp.X(), temp.Y() + 120);
	}
	return temp;
}
