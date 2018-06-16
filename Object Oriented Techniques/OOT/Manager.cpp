#include "Manager.h"

//Constructer
Manager::Manager()
{
	cubed = 25;
	Cols = (600 / cubed);
	Rows = (500 / cubed);
	particle_id = 0;
	hMc = 10;
	addingTimer = 0;
	
	for (int x = 0; x < hMc; x++)
	{
		RandomCell = rand() % 480;
		randomNumbers.push_back(RandomCell);
	}
	collisionCounter = 0;

	FPS = 0;
	frames = 0;
	starttime = 0;
	timepassed = difftime(time(0), start);
	starttime = timepassed;

	font = TTF_OpenFont("../Dependency/SDL2_TTF/font/arial.ttf", 24);

	
	/*
	This Bool decides if you are going to be checking collison on all of the buckets at
	once, or if it just checks a few random buckets at a time
	If this is true you should keep the number of particles low :/ fair warning
	*/

	CollisionType = false;

	if (CollisionType == true)
	{
		numOparticles = 1000;
	}
	else
	{
		numOparticles = 2000;
	}

	AddingParticle(numOparticles);
}

//Deconstructer
Manager::~Manager()
{

}

void Manager::Update(float deltaTs)
{
	
	
	if (CollisionType == false)
	{
		CollisionChecks();
	}
	
	ParticleUpdates(deltaTs);
	AmountUpdate();
	UpdateFPS();
}

void Manager::CollisionChecks()
{
	if (collisionCounter >= 400)
	{
		randomNumbers.clear();
		for (int x = 0; x < hMc; x++)
		{
			RandomCell = rand() % 480;
			randomNumbers.push_back(RandomCell);
		}
		collisionCounter = 0;
	}

	colParticles = _hashtable.checking2(randomNumbers);


	collisionCounter++;
}

void Manager::ParticleUpdates(float deltaTs)
{
	if (CollisionType == true)
	{
		colParticles = _hashtable.checking();
	}

	for (int i = 0; i < _particles.size(); i++)
	{

		int id = _particles.at(i)->GetID();

		for (int x = 0; x < colParticles.size(); x++)
		{
			if (id == colParticles.at(x))
			{
				_particles.at(i)->ChangeDirO();
			}
		}
	
		bool changeDirection = _collision.CollideWall(_particles.at(i)->GetPosition());

		if (changeDirection == true)
		{
			_particles.at(i)->ChangeDir();
		}

		_particles.at(i)->Update(deltaTs);

		int oldB = _particles.at(i)->GetBucket();
		int newB = _particles.at(i)->GetNewBucket();
		Vec2 pos = _particles.at(i)->GetPosition();
		id = _particles.at(i)->GetID();

		if (newB != oldB)
		{
			int check = _hashtable.UpdateKey(oldB, pos, id);

			if (check == 1)
			{
				_particles.erase(_particles.begin() + i);
				AddingParticle(1);
			}

			_particles.at(i)->UpdateBucket();

			
		}
	}
}

void Manager::AddingParticle(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		Vec2 position = { rand() % 550 + 25 , rand() % 450 + 25 };
		_particles.push_back(new Particles(position, particle_id));
		int check = _hashtable.input(position, particle_id);
		if (check == 1)
		{
			particle_id--;
			_particles.erase(_particles.end());
			amount++;
		}
		particle_id++;
	}
}

void Manager::DeletingParticle(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		int bucket = _particles.at(0)->GetBucket();
		int id = _particles.at(0)->GetID();
		_hashtable.remove(bucket, id);
		_particles.erase(_particles.begin());
	}
}

void Manager::AmountUpdate()
{
	const Uint8* key = SDL_GetKeyboardState(NULL);
	addingTimer++;

	if (key[SDL_SCANCODE_E] && addingTimer > 5)
	{
		numOparticles += 50;
		AddingParticle(50);
		addingTimer = 0;
	}
	if (key[SDL_SCANCODE_Q] && addingTimer > 5)
	{
		if (!numOparticles <= 0)
		{
			numOparticles -= 50;
			DeletingParticle(50);
			addingTimer = 0;
		}
	}
}

void Manager::Draw(SDL_Renderer* renderer)
{
	for (int x = 0; x < 600; x = x + cubed)
	{
		for (int y = 0; y < 500; y = y + cubed)
		{
			int fY = (y / 25);
			int fX = (x / 25);
			int checking = (((fX * 20) + fY) + 1);
			
			if (CollisionType == false)
			{
				for (int x = 0; x < hMc; x++)
				{
					if (checking == randomNumbers.at(x))
					{
						SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);
						x = 10000000;
					}
					else
					{
						SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
					}
				}
			}
			else 
			{
				SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
			}
			SDL_Rect grid;
			grid.x = x;
			grid.y = y;
			grid.w = cubed;
			grid.h = cubed;
			SDL_RenderDrawRect(renderer, &grid);
		}
	}

	for (int i = 0; i < _particles.size(); i++)
	{
		_particles.at(i)->Draw(renderer);
	}
	Writing(renderer);
}

void Manager::Writing(SDL_Renderer* renderer)
{
	std::stringstream fps;
	fps << FPS;
	SDL_Rect txtRect = { 5,10,50,50 };
	SDL_Color Green = { 0,255,0 };
	SDL_Surface* imageTxt = TTF_RenderText_Solid(font, "FPS : ", Green);
	SDL_Texture* sprite = SDL_CreateTextureFromSurface(renderer, imageTxt);

	SDL_RenderCopy(renderer, sprite, NULL, &txtRect);

	txtRect = { 50,10,50,50 };
	imageTxt = TTF_RenderText_Solid(font, fps.str().c_str(), Green);
	sprite = SDL_CreateTextureFromSurface(renderer, imageTxt);
	SDL_RenderCopy(renderer, sprite, NULL, &txtRect);

	txtRect = { 375,10,125,50 };
	imageTxt = TTF_RenderText_Solid(font, "Particles : ", Green);
	sprite = SDL_CreateTextureFromSurface(renderer, imageTxt);
	SDL_RenderCopy(renderer, sprite, NULL, &txtRect);
	
	std::stringstream nOp;
	nOp << numOparticles;
	txtRect = { 500,10,100,50 };
	imageTxt = TTF_RenderText_Solid(font, nOp.str().c_str(), Green);
	sprite = SDL_CreateTextureFromSurface(renderer, imageTxt);
	SDL_RenderCopy(renderer, sprite, NULL, &txtRect);
}

void Manager::UpdateFPS()
{
	timepassed = difftime(time(0), start);
	frames++;

	if (timepassed - starttime > 0.10 && frames > 10)
	{
		FPS = (double)frames / (timepassed - starttime);
		starttime = timepassed;
		frames = 0;
	}
}
