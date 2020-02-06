#pragma once

#include "Component.h"
#include "Vector2.h"
class PositionComponent : public Component
{
public:
	PositionComponent();
	~PositionComponent();
	PositionComponent(Vector2 position);
	Vector2 getPosition();
	void setPosition(Vector2 position);
	void init() override;
	void update() override;
	void render() override;
private:
	Vector2 m_position;
};

