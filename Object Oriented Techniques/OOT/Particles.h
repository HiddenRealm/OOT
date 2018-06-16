#pragma once
#include <cstdlib>
#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Vec2.h"
#include "Vec3.h"

class Particles
{
public:
	//Constructer - Deconstructer
	Particles(Vec2 pos, int id);
	~Particles();

	void Update(float deltaTs);

	void Draw(SDL_Renderer* renderer);
	void Move(float deltaTs);
	void ChangeDir();
	void ChangeDirO();

	void SetColour();

	int GetBucket();
	int GetNewBucket();
	void UpdateBucket();
	int GetID();
	Vec2 GetPosition();

private:
	int cubed, bucket, newBucket, dirX, dirY, particle_id, timerX, timerY, timerZ;
	Vec2 position;
	Vec3 normal = { 255,255,255 }, orange = { 255,165,0 }, magenta = { 204,0,204 };
	float speed;
};