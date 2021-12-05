#pragma once

#include <vector>
#include "GameObject.h"

class Bullet : public GameObject
{
public :

	Bullet(SDL_Texture* asset1Texture, SDL_Texture* asset2Texture, SDL_Renderer* R, int x, int y, int w, int h, int vx, int vy);

	void destroy();
};

class Gun
{
public :

	Gun(const char* asset1Location, const char* asset2Location, SDL_Renderer* R);
	Gun(SDL_Texture* asset1Texture, SDL_Texture* asset2Texture, SDL_Renderer* R);

	void shootBullet(SDL_Texture* asset1Texture, SDL_Texture* asset2Texture, SDL_Renderer* R, int x, int y, int vx, int vy);
	void renderBullet();
	void removeBullet();

protected :

	int bulletCooldownThresh;
	int bulletSize;
	int bulletCooldown;
	std::vector<Bullet> bulletList;

	SDL_Texture* bulletTexture;
	SDL_Texture* bulletBlastTexture;
};

