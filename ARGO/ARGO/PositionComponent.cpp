#include "PositionComponent.h"

PositionComponent::PositionComponent()
{
}

PositionComponent::~PositionComponent()
{
}

PositionComponent::PositionComponent(Vector2 position)
{
	m_position = position;
}

void PositionComponent::init()
{

}

void PositionComponent::update()
{

}

void PositionComponent::render()
{
}

void PositionComponent::setPosition(Vector2 position)
{
	m_position = position;
}

Vector2 PositionComponent::getPosition()
{
	return m_position;
}
