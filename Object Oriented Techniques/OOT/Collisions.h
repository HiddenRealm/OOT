#pragma once
#include <vector>

#include "Vec2.h"


class Collisions
{
public:
	Collisions();
	~Collisions();

	bool CollideObject(Vec2 pos1, Vec2 pos2);
	bool CollideWall(Vec2 pos);

private:
	int  width, height;
};