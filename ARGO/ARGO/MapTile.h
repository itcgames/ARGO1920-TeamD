#pragma once
#include "Sprite.h"
#include "PositionComponent.h"
class mapTile
{
public:
	mapTile();
	~mapTile();

	Sprite m_tile;
	Vector2 vec;
	void init(std::string t_spriteToLoad, SDL_Renderer*& t_renderer) {
		m_tile.loadFromFile(t_spriteToLoad, t_renderer);
		//m_tile.setRect(0, 0, 50, 50);
		
	}
	void setPos(Vector2 t_vec) { vec = t_vec; };
	void render(SDL_Renderer*& t_renderer) { m_tile.render(vec.x, vec.y, t_renderer); };
	
};