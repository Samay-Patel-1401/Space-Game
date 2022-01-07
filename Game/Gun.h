#pragma once

#include <vector>
#include "GameObject.h"

class Bullet : public GameObject
{
public :

	Bullet(SDL_Texture* asset1Texture, SDL_Texture* asset2Texture, SDL_Renderer* R, int x, int y, int w, int h, int vx, int vy, Mix_Chunk* explosionEffect);
};

class Gun
{
public :

	Gun(const char* asset1Location, const char* asset2Location, SDL_Renderer* R, const char* sound1Location, const char* sound2Location);
	Gun(SDL_Texture* asset1Texture, SDL_Texture* asset2Texture, SDL_Renderer* R, Mix_Chunk* explosionEffect, Mix_Chunk* fireEffect);

	void shootBullet(SDL_Texture* asset1Texture, SDL_Texture* asset2Texture, SDL_Renderer* R, int x, int y, int vx, int vy);
	void renderBullet();
	void removeBullet();
	void cleanGun();

protected :

	int bulletCooldownThresh;
	int bulletSize;
	int bulletCooldown;
	std::vector<Bullet> bulletList;

	SDL_Texture* bulletTexture;
	SDL_Texture* bulletBlastTexture;
	Mix_Chunk* bulletExplosionSound;
	Mix_Chunk* bulletFireSound;
};

