#pragma once
#include "PositionComponent.h"
#include <string>
class MovementSystem
{
public:
	MovementSystem();
	~MovementSystem();
	
	void move(PositionComponent &pos, std::string t_dir);
	

private:
	
};

