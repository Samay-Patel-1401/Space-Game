#include "Gun.h"

Bullet::Bullet(SDL_Texture* asset1Texture, SDL_Texture* asset2Texture, SDL_Renderer* R, int x, int y, int w, int h, int vx, int vy, Mix_Chunk* explosionEffect) : GameObject(asset1Texture, asset2Texture, R, x, y, w, h, vx, vy, explosionEffect)
{
	explosionSize = 0;
	explosionSizeThresh = 40;
	delExplosion = 1;
}

void Bullet::destroy()
{
	isDestroyed = true;

	return;
}

Gun::Gun(const char* asset1Location, const char* asset2Location, SDL_Renderer* R, const char* sound1Location, const char*sound2Location)
{
	bulletTexture = loadTexture(asset1Location, R);
	bulletBlastTexture = loadTexture(asset2Location, R);

	bulletCooldownThresh = 60;
	bulletSize = 8;
	bulletCooldown = bulletCooldownThresh;

	bulletExplosionSound = Mix_LoadWAV(sound1Location);
	bulletFireSound = Mix_LoadWAV(sound2Location);
}

Gun::Gun(SDL_Texture* asset1Texture, SDL_Texture* asset2Texture, SDL_Renderer* R, Mix_Chunk* explosionEffect, Mix_Chunk* fireEffect)
{
	bulletTexture = asset1Texture;
	bulletBlastTexture = asset2Texture;

	bulletCooldownThresh = 60;
	bulletSize = 7;
	bulletCooldown = bulletCooldownThresh;

	bulletExplosionSound = explosionEffect;
	bulletFireSound = fireEffect;
}

void Gun::shootBullet(SDL_Texture* asset1Texture, SDL_Texture* asset2Texture, SDL_Renderer* R, int x, int y, int vx, int vy)
{
	if (bulletCooldown == bulletCooldownThresh)
	{
		Bullet B(asset1Texture, asset2Texture, R, x - bulletSize / 2, y - bulletSize / 2, bulletSize, bulletSize, vx, vy, bulletExplosionSound);

		if (!B.destructionStatus())
		{
			Mix_PlayChannel(-1, bulletFireSound, 0);
			bulletList.push_back(B);
			bulletCooldown = 0;
		}
	}

	return;
}

void Gun::removeBullet()
{
	for (int i = 0; i < bulletList.size(); i++)
	{
		SDL_Rect rect = bulletList[i].getdstRect();

		if (bulletList[i].destructionStatus())
		{
			bulletList.erase(bulletList.begin() + i);
			i--;
		}
	}

	return;
}

void Gun::renderBullet()
{
	for (int i = 0; i < bulletList.size(); i++)
	{
		bulletList[i].objRender();
	}

	if (bulletCooldown < bulletCooldownThresh)
		bulletCooldown++;

	return;
}

void Gun::cleanGun()
{
	Mix_HaltChannel(-1);
	Mix_FreeChunk(bulletExplosionSound);
	Mix_FreeChunk(bulletFireSound);

	SDL_DestroyTexture(bulletTexture);
	SDL_DestroyTexture(bulletBlastTexture);

	return;
}