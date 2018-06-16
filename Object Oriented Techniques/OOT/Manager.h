#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <string>

#include "SDL_ttf.h"
#include "ItemKey.h"
#include "Particles.h"
#include "HashTable.h"
#include "Collisions.h"

class Particles;

class Manager
{
public:
	//Constructer - Deconstrucer
	Manager();
	~Manager();

	void Update(float deltaTs);

	void Draw(SDL_Renderer* renderer);
	void Writing(SDL_Renderer* renderer);
	void ParticleUpdates(float deltaTs);
	void AmountUpdate();
	void AddingParticle(int amount);
	void DeletingParticle(int amount);
	void CollisionChecks();
	void UpdateFPS();

private:
	std::vector<Particles*> _particles;
	int Cols, Rows, cubed, particle_id, addingTimer, RandomCell, hMc;
	int collisionCounter;
	HashTable _hashtable;
	Collisions _collision;
	int numOparticles;

	bool CollisionType;
	std::vector<int> colParticles;
	std::vector<int> randomNumbers;

	TTF_Font* font;
	int frames;
	double starttime;
	float FPS, timepassed;
	time_t start = time(0);
};