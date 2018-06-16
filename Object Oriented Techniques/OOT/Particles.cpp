#include "Particles.h"

//Constructer
Particles::Particles(Vec2 pos, int id)
{
	cubed = 2;

	position.x = pos.x;
	position.y = pos.y;
	particle_id = id;
	timerX = 0;
	timerY = 0;
	timerZ = 0;

	speed = 30;
	dirX = rand() % 3 - 1;
	dirY = rand() % 3 - 1;

	if (dirX == 0 && dirY == 0)
	{
		dirY++;
	}

	int x = position.x / 25;
	int y = position.y / 25;
	bucket = (((x * 20) + y) + 1);
	newBucket = bucket;
}

//Deconstructer
Particles::~Particles()
{

}

void Particles::Update(float deltaTs)
{
	Move(deltaTs);

	timerX--;
	timerY--;
	timerZ--;
	int x = position.x / 25;
	int y = position.y / 25;
	newBucket = (((x * 20) + y) + 1);
}

void Particles::Draw(SDL_Renderer* renderer)
{
	SetColour();
	SDL_SetRenderDrawColor(renderer, normal.r, normal.g, normal.b, 255);
	SDL_Rect particle;
	particle.x = position.x;
	particle.y = position.y;
	particle.w = cubed;
	particle.h = cubed;

	SDL_RenderDrawRect(renderer, &particle);
}

void Particles::Move(float deltaTs)
{
	position.x += dirX * speed * deltaTs;
	position.y += dirY * speed * deltaTs;
}

void Particles::SetColour()
{
	if (timerX > 0 || timerY > 0)
	{
		normal = orange;
	}
	else if (timerZ > 0)
	{
		normal = magenta;
	}
	else
	{
		normal = { 255,255,255 };
	}
}

void Particles::ChangeDirO()
{
	if (timerZ <= 0)
	{
		dirX = rand() % 3 - 1;
		dirY = rand() % 3 - 1;

		if (dirX == 0 && dirY == 0)
		{
			dirY++;
		}
		timerZ = 50;
	}
}

void Particles::ChangeDir()
{
	if (position.x <= 1 || position.x >= 599)
	{
		if (timerX <= 0)
		{
			if (dirX < 0)
			{
				dirX = abs(dirX);
			}
			else
			{
				dirX *= -1;
			}
			timerX = 20;
		}
	}
	
	if (position.y <= 1 || position.y >= 499)
	{
		if (timerY <= 0)
		{
			if (dirY < 0)
			{
				dirY = abs(dirY);
			}
			else
			{
				dirY *= -1;
			}
			timerY = 20;
		}
	}
}

int Particles::GetBucket()
{
	return bucket;
}

int Particles::GetNewBucket()
{
	return newBucket;
}

void Particles::UpdateBucket()
{
	bucket = newBucket;
}

int Particles::GetID()
{
	return particle_id;
}

Vec2 Particles::GetPosition()
{
	return position;
}