#pragma once
#include<vector>
#include<memory>
#include"Component.h"
class Entity
{
public:
	Entity();
	~Entity();
	void update();
	void draw();
	void getActive();
	void setActiveFalse();

private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;



};
