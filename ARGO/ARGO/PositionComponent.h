#pragma once

#include "Component.h"
#include "Vector2.h"
#include <stack>
class PositionComponent : public Component
{
public:
	PositionComponent();
	~PositionComponent();
	PositionComponent(Vector2 position);
	Vector2 getPosition();
	void setPosition(Vector2 position);
	void setPreviousPosition(Vector2 position);
	Vector2 getPreviousPosition();
	void setToPreviousPos();
	void init() override;
	void update() override;
	void render() override;
private:
	Vector2 m_position;
	std::stack<Vector2> m_prevPositions[];
};

