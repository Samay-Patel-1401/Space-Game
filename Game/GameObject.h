#pragma once

#include <SDL.h>
#include <iostream>
#include "Additional.h"
#include <SDL_mixer.h>

class GameObject
{
public :

	GameObject(const char* assetLocation, const char* asset2Location, SDL_Renderer* R, int x, int y, int w, int h, int vx, int vy, const char* soundLocation);
	GameObject(SDL_Texture* objTexture, SDL_Texture* blastTexture, SDL_Renderer* R, int x, int y, int w, int h, int vx, int vy, Mix_Chunk* explosionEffect);
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
	Mix_Chunk* explosionSound;

private :

	SDL_Rect dstRect;
	float location[2];
	bool soundFlag;
};

