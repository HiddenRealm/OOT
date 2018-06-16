#pragma once

#include <list>
#include <vector>

#include "Collisions.h"
#include "Vec2.h"
#include "ItemKey.h"

class HashTable
{
public:
	//Constructer - Deconstructer
	HashTable();
	~HashTable();

	int input(Vec2 key, int id);
	int hashKey(Vec2 key);

	int UpdateKey(int bucket, Vec2 newBucket, int id);
	void remove(int bucket, int id);
	std::vector<int> checking();
	std::vector<int> checking2(std::vector<int> nums);

private:
	int Cols, Rows, cubed;
	Collisions _collision;
	std::vector<std::list<ItemKey>> table;
};