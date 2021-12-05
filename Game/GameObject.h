#pragma once

#include <SDL.h>
#include <iostream>
#include "Additional.h"

class GameObject
{
public :

	GameObject(const char* assetLocation, const char* asset2Location, SDL_Renderer* R, int x, int y, int w, int h, int vx, int vy);
	GameObject(SDL_Texture* objTexture, SDL_Texture* blastTexture, SDL_Renderer* R, int x, int y, int w, int h, int vx, int vy);
	~GameObject();

	void objRender();
	SDL_Rect* updateGameObject();
	SDL_Rect getdstRect();
	void clean();
	void onExplosion();
	bool status();
	bool destructionStatus();

protected :

	int velocity[2];

	int explosionSizeThresh;
	int explosionSize;
	int delExplosion;
	bool isDestroyed;

	SDL_Texture* objTexture;
	SDL_Texture* blastTexture;
	SDL_Renderer* renderer;

private :

	SDL_Rect dstRect;
	float location[2];
};

