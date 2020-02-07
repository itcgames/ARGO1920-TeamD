#pragma once
#include"Component.h"
#include<vector>
#include<memory>

class Entity
{
private:
	bool alive = true;
	
	int componentIDCounter = 0;
	int uniqueID;

public:
	std::vector<std::unique_ptr<Component>> components;
	Entity();
	bool getAlive();
	void setAliveFalse();
	int getUniqueID();
	void update();
	void render();
};
