#include "AnimationStates.h"

void Idle::moving(Animation* a)
{
	std::cout << "moving" << std::endl;
	a->setCurrent(new Moving());
	delete this;
}

void Moving::idle(Animation* a)
{
	std::cout << "moving to idling" << std::endl;
	a->setCurrent(new Idle());
	delete this;
}
void Moving::pushing(Animation* a)
{
	std::cout << "moving to pushing" << std::endl;
	a->setCurrent(new Pushing());
	delete this;
}
void Moving::dying(Animation* a)
{
	std::cout << "moving to dying" << std::endl;
	a->setCurrent(new Dying());
	delete this;
}

void Pushing::idle(Animation* a)
{
	std::cout << "pushing to idle" << std::endl;
	a->setCurrent(new Idle());
	delete this;
}

void Dying::idle(Animation* a)
{
	std::cout << "dying to idle" << std::endl;
	a->setCurrent(new Idle());
	delete this;
}