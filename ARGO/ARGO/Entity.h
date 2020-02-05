#pragma once
#include"Component.h"
#include<vector>
#include<memory>

class Entity
{
private:
	bool alive = true;
	std::vector<std::unique_ptr<Component>> components;
	int componentIDCounter = 0;
	int uniqueID;

public:
	Entity();
	bool getAlive();
	void setAliveFalse();
	int getUniqueID();
	void update();
	void render();
};
