#include "VelocityComponent.h"

VelocityComponent::VelocityComponent()
{
	
}

void VelocityComponent::init()
{

}

void VelocityComponent::update()
{

}

void VelocityComponent::setVelocity(Vector2 velocity)
{
	m_velocity = velocity;
}

Vector2 VelocityComponent::getVelocity()
{
	return m_velocity;
}