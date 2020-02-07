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
	m_position.x++;
	m_position.y++;

	std::cout << m_position.x << ", " << m_position.y << std::endl;
}

void PositionComponent::render()
{
}

void PositionComponent::setPosition(Vector2 position)
{
	m_position = position;
}

void PositionComponent::setPreviousPosition(Vector2 position)
{
	m_prevPositions->push(position);
}

Vector2 PositionComponent::getPreviousPosition()
{
	return m_prevPositions->top();
}

void PositionComponent::setToPreviousPos()
{
	if (!m_prevPositions->empty())
	{
		m_position = m_prevPositions->top();
		m_prevPositions->pop();
	}
	
}

Vector2 PositionComponent::getPosition()
{
	return m_position;
}
