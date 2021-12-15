#include "GameObject.h"

GameObject::GameObject(const char* assetLocation, const char* asset2Location, SDL_Renderer* R, int x, int y, int w, int h, int vx, int vy, const char* soundLocation)
{
	renderer = R;

	objTexture = loadTexture(assetLocation, renderer);
	blastTexture = loadTexture(asset2Location, renderer);

	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = w;
	dstRect.h = h;

	velocity[0] = vx;
	velocity[1] = vy;

	location[0] = x;
	location[1] = y;

	explosionSize = 10;
	explosionSizeThresh = 100;
	delExplosion = 2;

	isDestroyed = false;

	explosionSound = Mix_LoadWAV(soundLocation);
	soundFlag = true;

	objStrength = 10;
	delObjStrength = 10;

	std::cout << "Game Object Created...." << std::endl;
}

GameObject::GameObject(SDL_Texture* ObjTexture, SDL_Texture* BlastTexture, SDL_Renderer* R, int x, int y, int w, int h, int vx, int vy, Mix_Chunk* explosionEffect)
{
	objTexture = ObjTexture;
	blastTexture = BlastTexture;
	renderer = R;

	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = w;
	dstRect.h = h;

	velocity[0] = vx;
	velocity[1] = vy;

	location[0] = x;
	location[1] = y;

	explosionSize = 10;
	explosionSizeThresh = 100;
	delExplosion = 2;

	isDestroyed = false;

	explosionSound = explosionEffect;
	soundFlag = true;

	std::cout << "Game Object Created...." << std::endl;
}

GameObject::~GameObject()
{
	std::cout << "Game Object Cleaned!!" << std::endl;
}

void GameObject::objRender()
{
	if (isDestroyed)
		onExplosion();
	else
		SDL_RenderCopy(renderer, objTexture, nullptr, updateGameObject());

	return;
}

SDL_Rect* GameObject::updateGameObject()
{
	location[0] += ((float)velocity[0])/20.0;
	location[1] += ((float)velocity[1])/20.0;

	dstRect.x = location[0];
	dstRect.y = location[1];

	return &dstRect;
}

void GameObject::clean()
{
	SDL_DestroyTexture(objTexture);
	SDL_DestroyTexture(blastTexture);
	Mix_HaltChannel(-1);
	Mix_FreeChunk(explosionSound);

	return;
}

SDL_Rect GameObject::getdstRect()
{
	return dstRect;
}

bool GameObject::destructionStatus()
{
	if (explosionSize > explosionSizeThresh and isDestroyed)
		return true;
	else if (dstRect.x < -dstRect.w or dstRect.x > 1000 or dstRect.y < -dstRect.h or dstRect.y > 750)
		return true;
	else
		return false;
}

bool GameObject::status()
{
	return isDestroyed;
}

void GameObject::onExplosion()
{
	if (explosionSize <= explosionSizeThresh)
	{
		if (soundFlag)
		{
			soundFlag = false;
			Mix_PlayChannel(-1, explosionSound, 0);
		}

		SDL_Rect Rect = getdstRect();
		Rect.x += (Rect.w - explosionSize) / 2;
		Rect.y += (Rect.h - explosionSize) / 2;
		Rect.w = explosionSize;
		Rect.h = explosionSize;

		SDL_RenderCopy(renderer, blastTexture, nullptr, &Rect);

		explosionSize += delExplosion;
	}

	return;
}

void GameObject::onCollision()
{
	objStrength -= delObjStrength;
	if (objStrength == 0)
		isDestroyed = true;

	return;
}