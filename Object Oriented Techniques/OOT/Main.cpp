#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Manager.h"

//Main
int main(int argc, char* argv[])
{
	//Initializing the window and renderer
	SDL_Window* window;
	SDL_Renderer* renderer;

	//Initializing SDL & TTF;
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	//Creates the demo window
	window = SDL_CreateWindow("Spatial Hasing Collision", 100, 100, 600, 500, SDL_WINDOW_SHOWN);

	//Renderers the Window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//Getting the "LastTime" for calculating deltaTs
	unsigned int lastTime = SDL_GetTicks();
	srand(time(NULL));

	//Class
	Manager myScene;

	SDL_Event e;

	//RealTimeLoop 
	while (true)
	{
		//Current time is also needed
		unsigned int current = SDL_GetTicks();
		float deltaTs = (float)(current - lastTime) / 1000.0f;
		lastTime = current;

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				return 0;
			}
		}



		//Clear the Screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		

		//Draw
		myScene.Update(deltaTs);
		myScene.Draw(renderer);
		

		//Update the Screen
		SDL_RenderPresent(renderer);


		// Limiter in case we're running really quick
		if (deltaTs < (1.0f / 50.0f))	// not sure how accurate the SDL_Delay function is..
		{
			SDL_Delay((unsigned int)(((1.0f / 50.0f) - deltaTs)*1000.0f));
		}
	}

	TTF_Quit();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
