#ifndef CHARACTER
#define CHARACTER
#include <iostream>
#include "Entity.h"
#include "Vector2.h"
class Character
{
public:
	Character() {}
	virtual ~Character() {}
	virtual void draw() = 0;
};
#endif // CHARACTER

#ifndef CAT
#define CAT
class Cat: public Character
{

public:
	void draw() { std::cout << "drawing cat" << std::endl; }
};
#endif

#ifndef FLAG
#define FLAG
class Flag: public Character
{

public:
	void draw() { std::cout << "drawing flag" << std::endl; }
};
#endif
