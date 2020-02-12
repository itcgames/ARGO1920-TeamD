#pragma once
#include "SpriteComponent.h"
#include "PositionComponent.h"
class mapTile
{
public:
	mapTile();
	~mapTile();

	SpriteComponent m_tile;
	Vector2 vec;
	void init(std::string t_spriteToLoad, SDL_Renderer*& t_renderer) {
		m_tile.setPathAndScreen(t_spriteToLoad, t_renderer);
		//m_tile.setRect(0, 0, 50, 50);
		
	}
	void setPos(Vector2 t_vec) { vec = t_vec; m_tile.setPosAndSize(vec.x, vec.y, 120, 120); };
	void render(SDL_Renderer*& t_renderer) { m_tile.render(); };
	
};