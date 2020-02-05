#pragma once
#include"Entity.h"
class Component
{
public:
	Entity* entity;
	
	virtual void init();
	virtual void update();
	virtual void render();

	virtual ~Component();
};
