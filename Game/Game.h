#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "User.h"

class Game
{
public :

	Game();
	~Game();

	void initWindow(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void initAudio();
	void handleEvent();
	bool status();
	SDL_Renderer* getRenderer();
	SDL_Event* getEvent();

private :

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event* event;
	bool isRunning;
};

