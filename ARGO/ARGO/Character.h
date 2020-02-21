#ifndef CHARACTER
#define CHARACTER
#include <iostream>
#include "Entity.h"
#include "Vector2.h"
#include "AudioComponent.h"
class Character
{
public:
	Character() {}
	virtual ~Character() {}
	virtual void addAudio() = 0;
};
#endif // CHARACTER

#ifndef CAT
#define CAT
class Cat: public Character
{

public:
	void addAudio() { std::cout << "drawing cat" << std::endl; }
};
#endif

#ifndef FLAG
#define FLAG
class Flag: public Character
{

public:
	void addAudio() { std::cout << "drawing flag" << std::endl; }
};
#endif
