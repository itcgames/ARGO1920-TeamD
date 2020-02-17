#include "OctTree.h"

OctTree::OctTree()
{
}

OctTree::~OctTree()
{
}

void OctTree::initTree(Vector2 box1Pos, Vector2 boxSize, Vector2 box2Pos, Vector2 box3Pos, Vector2 box4Pos, Vector2 box5Pos, Vector2 box6Pos,Vector2 box7Pos,Vector2 box8Pos)
{
	pos[0] = box1Pos;
	pos[1] = box2Pos;
	pos[2] = box3Pos;
	pos[3] = box4Pos;
	pos[4] = box5Pos;
	pos[5] = box6Pos;
	pos[6] = box7Pos;
	pos[7] = box8Pos;
	size = boxSize;
}
