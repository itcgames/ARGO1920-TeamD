#include"System.h"

System::System()
{
}

System::~System()
{
}

void System::movementUp()
{
	for (auto const& Entity : entityArr)
	{
		//move up
	}
}

void System::movementDown()
{
	for (auto const& Entity : entityArr)
	{
		//move down
	}
}

void System::movementLeft()
{
	for (auto const& Entity : entityArr)
	{
		//move left
	}
}

void System::movementRight()
{
	for (auto const& Entity : entityArr)
	{
		//move right
	}
}

void System::platformCollision()
{
	std::vector<Component*> platPositions;
	std::vector<Component*> platSizes;
	for (auto const& currentEntity : entityArr)
	{
		if (true)//Entity.id() == "Platform")
		{
			for (auto const& currentComponent : currentEntity.components)
			{
				if (currentComponent.get() == new PositionComponent)
				{
					platPositions.push_back(currentComponent.get());
				}
				if (currentComponent.get() == new BodyComponent)
				{
					platSizes.push_back(currentComponent.get());
				}
			}
		}
	}
	for (auto const& currentEntity : entityArr)
	{
		Vector2 playerPos(0,0);
		Vector2 playerSize(0, 0);
		Component* pla = new PositionComponent();
		if (true)//Entity.id() == "Player")
		{
			for (auto const& currentComponent : currentEntity.components)
			{
				if (currentComponent.get() == new PositionComponent)
				{

				}
				if (currentComponent.get() == new BodyComponent)
				{

				}
			}
		}
	}
}
