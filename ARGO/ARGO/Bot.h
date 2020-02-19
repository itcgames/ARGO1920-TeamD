#pragma once
#include"Vector2.h"
class Bot
{
public:
	Bot();
	~Bot();
	Vector2 getPos();
	Vector2 getVelocity();

	void move();
	void collisionDetection();
	void boundaryDetection();
private:
	Vector2 m_pos;//probably won't use these
	Vector2 m_vel;//probably won't use
};
