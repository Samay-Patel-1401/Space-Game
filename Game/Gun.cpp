#include "Gun.h"

Bullet::Bullet(SDL_Texture* asset1Texture, SDL_Texture* asset2Texture, SDL_Renderer* R, int x, int y, int w, int h, int vx, int vy) : GameObject(asset1Texture, asset2Texture, R, x, y, w, h, vx, vy)
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

Gun::Gun(const char* asset1Location, const char* asset2Location, SDL_Renderer* R)
{
	bulletTexture = loadTexture(asset1Location, R);
	bulletBlastTexture = loadTexture(asset2Location, R);

	bulletCooldownThresh = 60;
	bulletSize = 8;
	bulletCooldown = bulletCooldownThresh;
}

Gun::Gun(SDL_Texture* asset1Texture, SDL_Texture* asset2Texture, SDL_Renderer* R)
{
	bulletTexture = asset1Texture;
	bulletBlastTexture = asset2Texture;

	bulletCooldownThresh = 60;
	bulletSize = 7;
	bulletCooldown = bulletCooldownThresh;
}

void Gun::shootBullet(SDL_Texture* asset1Texture, SDL_Texture* asset2Texture, SDL_Renderer* R, int x, int y, int vx, int vy)
{
	if (bulletCooldown == bulletCooldownThresh)
	{
		Bullet B(asset1Texture, asset2Texture, R, x - bulletSize / 2, y - bulletSize / 2, bulletSize, bulletSize, vx, vy);
		bulletList.push_back(B);
		bulletCooldown = 0;
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