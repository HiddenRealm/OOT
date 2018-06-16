#pragma once
#include "Vec2.h"

struct ItemKey
{
	Vec2 key;
	int id;
	ItemKey* next;
};