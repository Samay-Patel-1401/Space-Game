#include "Gun.h"

Bullet::Bullet(SDL_Texture* asset1Texture, SDL_Texture* asset2Texture, SDL_Renderer* R, int x, int y, int w, int h, int vx, int vy) : GameObject(asset1Texture, asset2Texture, R, x, y, w, h, vx, vy)
{
	explosionSize = 0;
	explosionSizeThresh = 40;
	delExplosion = 1;
}

bool Bullet::destructionStatus()
{
	if (explosionSize > explosionSizeThresh and isDestroyed)
		return true;
	else
		return false;
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
	bulletSize = 7;
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

Gun::~Gun()
{
	SDL_DestroyTexture(bulletTexture);
	SDL_DestroyTexture(bulletBlastTexture);
}

void Gun::shootBullet(SDL_Texture* asset1Texture, SDL_Texture* asset2Texture, SDL_Renderer* R, SDL_Rect rect, int vx, int vy)
{
	if (bulletCooldown == bulletCooldownThresh)
	{
		Bullet B(asset1Texture, asset2Texture, R, rect.x + rect.w / 2, rect.y, bulletSize, bulletSize, vx, vy);
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

		if (rect.y < -10 or bulletList[i].destructionStatus())
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