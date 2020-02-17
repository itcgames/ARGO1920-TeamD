#pragma once
#include <iostream>
#include "Animation.h"
class State
{
public:
	virtual void idle(Animation* a)
	{
		std::cout << "State::Idling" << std::endl;
	}

	virtual void moving(Animation* a)
	{
		std::cout << "State::moving" << std::endl;
	}
	virtual void pushing(Animation* a)
	{
		std::cout << "State::pushing" << std::endl;
	}
	virtual void dying(Animation* a)
	{
		std::cout << "State::dying" << std::endl;
	}
};

class Idle : public State
{
public:
	Idle() {}
	void moving(Animation* a);
};

class Moving : public State
{
public:
	Moving() {}
	void idle(Animation* a);
	void pushing(Animation* a);
	void dying(Animation* a);
};
class Pushing : public State
{
public:
	Pushing() {}
	void idle(Animation* a);
};
class Dying : public State
{
public:
	Dying() {}
	void idle(Animation* a);
};