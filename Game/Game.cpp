#include "Game.h"

Game::Game()
{
	window = nullptr;
	renderer = nullptr;
	isRunning = false;
	event = new SDL_Event;
}

Game::~Game()
{
	delete event;

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game Cleaned...." << std::endl;

	std::cout << "Game Finished.";
}

void Game::initWindow(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flag = 0;
	if (fullscreen)
	{
		flag = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL subsystem initialized....." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flag);
		if (window == NULL)
		{
			std::cout << "Window Error...." << SDL_GetError() << std::endl;
			return;
		}
		
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
		{
			std::cout << "Renderer Error...." << SDL_GetError() << std::endl;
			return;
		}
		isRunning = true;
	}
	else
	{
		std::cout << "SDL subsystem Error...." << SDL_GetError() << std::endl;
	}

	return;
}

void Game::handleEvent()
{
	SDL_PollEvent(event);

	if (event->type == SDL_QUIT)
	{
		isRunning = false;
	}

	return;
}

SDL_Renderer* Game::getRenderer()
{
	return renderer;
}

SDL_Event* Game::getEvent()
{
	return event;
}

bool Game::status()
{
	return isRunning;
}