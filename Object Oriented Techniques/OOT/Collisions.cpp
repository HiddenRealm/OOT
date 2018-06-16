#include "Collisions.h"

//Constructer & Deconstructer
Collisions::Collisions()
{
	width = 600; height = 500;

}

Collisions::~Collisions()
{

}

bool Collisions::CollideObject(Vec2 pos1, Vec2 pos2)
{
	if (pos1.x >= pos2.x && pos1.x <= (pos2.x + 1) || 
		(pos1.x + 1) >= pos2.x && (pos1.x + 1) <= (pos2.x + 1))
	{
		if (pos1.y >= pos2.y && pos1.y <= (pos2.y + 1) ||
			(pos1.y + 1) >= pos2.y && (pos1.y + 1) <= (pos2.y + 1))
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

bool Collisions::CollideWall(Vec2 pos)
{
	if (pos.x <= 1 || pos.x >= 599 || pos.y <= 1 || pos.y >= 499)
	{
		return true;
	}
	else
	{
		return false;
	}
}
