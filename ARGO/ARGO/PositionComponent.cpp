#include "PositionComponent.h"

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

void PositionComponent::setPosition(Vector2 position)
{
	m_position = position;
}

Vector2 PositionComponent::getPosition()
{
	return m_position;
}
