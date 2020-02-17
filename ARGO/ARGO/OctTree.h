#pragma once
#include "Vector2.h"

class OctTree
{
public:
	OctTree();
	~OctTree();

	//There will be 6 sections.
	void initTree(Vector2 box1Pos, Vector2 boxSize,
		Vector2 box2Pos, Vector2 box3Pos,
		Vector2 box4Pos, Vector2 box5Pos,
		Vector2 box6Pos,Vector2 box7Pos,
		Vector2 box8Pos);

	Vector2 getOct(int t_arrayPos) { return pos[t_arrayPos]; };
	Vector2 getSize() { return size; };
private:
	Vector2 pos[8];
	Vector2 size;
};

