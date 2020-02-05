#pragma once
#include"Component.h"
#include<vector>
#include<memory>

class Entity
{
private:
	bool alive = true;
	std::vector<std::unique_ptr<Component>> components;

public:
	bool getAlive();
	void setAliveFalse();
	void update();
	void render();
};
