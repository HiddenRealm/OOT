#include "HashTable.h"

#include <iostream>

HashTable::HashTable()
{
	cubed = 25;
	Cols = (600 / cubed);
	Rows = (500 / cubed);

	for (int i = 0; i < ((Cols * Rows) + 1); i++)
	{
		std::list<ItemKey> temp;
		table.push_back(temp);
	}
}

//Deconstructer
HashTable::~HashTable()
{

}

//Input function, this is where the particles positions get monitored
int HashTable::input(Vec2 key, int id)
{
	int bucket = hashKey(key);

	if (bucket > 480 || bucket < 0)
	{
		return 1;
	}
	
	std::list<ItemKey>::iterator it = table[bucket].begin();
	ItemKey particle;

	if (!table[bucket].empty())
	{
		while (it != table[bucket].end())
		{
			it++;
		}

		particle.key = key;
		particle.id = id;
		particle.next = nullptr;
		table[bucket].push_back(particle);
	}
	else
	{
		particle.key = key;
		particle.id = id;
		particle.next = nullptr;
		table[bucket].push_back(particle);
	}

	return 0;
}

std::vector<int> HashTable::checking()
{
	std::vector<int> IDs;
	
	for (int x = 0; x < table.size(); x++)
	{
		if (table[x].size() > 1)
		{
			std::list<ItemKey>::iterator it1 = table[x].begin();
			std::list<ItemKey>::iterator it2 = table[x].begin();
			it2++;
			while (it1 != table[x].end())
			{
				bool end = false;
				for (int i = 0; i < table[x].size(); i++)
				{
					while (it2 != table[x].end() && it1->id != it2->id && end == false)
					{
						Vec2 pos1 = it1->key;
						Vec2 pos2 = it2->key;

						bool check = _collision.CollideObject(pos1, pos2);

						if (check == true)
						{
							IDs.push_back(it1->id);
							end = true;
						}
						it2++;
					}
				}
				it2 = table[x].begin();
				it1++;
			}
		}
	}
	return IDs;
}

std::vector<int> HashTable::checking2(std::vector<int> nums)
{
	std::vector<int> IDs;
	for (int x = 0; x < nums.size(); x++)
	{
		if (table[nums.at(x)].size() > 1)
		{
			std::list<ItemKey>::iterator it1 = table[nums.at(x)].begin();
			std::list<ItemKey>::iterator it2 = table[nums.at(x)].begin();
			it2++;
			while (it1 != table[nums.at(x)].end())
			{
				bool end = false;
				for (int i = 0; i < table[nums.at(x)].size(); i++)
				{
					while (it2 != table[nums.at(x)].end() && it1->id != it2->id && end == false)
					{
						Vec2 pos1 = it1->key;
						Vec2 pos2 = it2->key;

						bool check = _collision.CollideObject(pos1, pos2);
						
						if (check == true)
						{
							IDs.push_back(it1->id);
							IDs.push_back(it2->id);
							end = true;
						}
						it2++;
					}
				}
				it2 = table[nums.at(x)].begin();
				it1++;
			}
		}
	}
	return IDs;
}

void HashTable::remove(int bucket, int id)
{
	std::list<ItemKey>::iterator it = table[bucket].begin();
	ItemKey particle;

	if (!table[bucket].empty())
	{
		while (it != table[bucket].end() && it->id != id)
		{
			it++;
		}
		table[bucket].erase(it);
	}
}

int HashTable::hashKey(Vec2 key)
{
	Vec2 hashing = { key.x, key.y };

	int y = (hashing.y / 25);
	int x = (hashing.x / 25);
	return (((x * 20) + y) + 1);
}

int HashTable::UpdateKey(int bucket, Vec2 newKey, int id)
{
	if (bucket > 480 || bucket < 0)
	{
		return 1;
	}
	
	std::list<ItemKey>::iterator it = table[bucket].begin();
	ItemKey particle;

	if (!table[bucket].empty())
	{
		while (it != table[bucket].end() && it->id != id)
		{
			it++;
		}
		table[bucket].erase(it);
	}

	input(newKey, id);
	return 0;
}