#include "Obstacle.h"

Astroid::Astroid(SDL_Texture* asset1Texture, SDL_Texture* asset2Texture, SDL_Renderer* R, int x, int y, int w, int h, int vx, int vy) : GameObject(asset1Texture, asset2Texture, R, x, y, w, h, vx, vy)
{
	explosionSize = 50;
	explosionSizeThresh = 80;
	delExplosion = 1;
}

Enemy::Enemy(SDL_Texture* asset1Texture, SDL_Texture* asset2Texture, SDL_Texture* asset3Texture, SDL_Texture* asset4Texture, SDL_Renderer* R, int x, int y, int w, int h, int vx, int vy) : GameObject(asset1Texture, asset2Texture, R, x, y, w, h, vx, vy), Gun(asset3Texture, asset4Texture, R)
{

}

bool Astroid::destructionStatus()
{
	if (explosionSize > explosionSizeThresh and isDestroyed)
		return true;
	else
		return false;
}

void Astroid::destroy()
{
	isDestroyed = true;
}

Obstacle::Obstacle(SDL_Renderer* R)
{
	obsSpeed = 50;
	renderer = R;
	spawnAlert = 30;

	blastTexture = loadTexture("Assets/whitePuff12.png", R);
	obsTexture.push_back(loadTexture("Assets/meteor_detailedSmall.png", R));
	obsTexture.push_back(loadTexture("Assets/meteor_squareDetailedSmall.png", R));
	obsTexture.push_back(loadTexture("Assets/meteor_large.png", R));
	obsTexture.push_back(loadTexture("Assets/meteor_squareLarge.png", R));
	obsTexture.push_back(loadTexture("Assets/meteor_detailedLarge.png", R));
	obsTexture.push_back(loadTexture("Assets/meteor_squareDetailedLarge.png", R));
}

Obstacle::~Obstacle()
{
	for (int i = 0; i < obsTexture.size(); i++)
	{
		SDL_DestroyTexture(obsTexture[i]);
	}
	SDL_DestroyTexture(blastTexture);
}

void Obstacle::generateObstacle()
{
	if (spawnAlert == spawnTime)
	{
		int obs = (rand() % 6);
		int x = (rand() % 860) + 50;
		int obsSize = 30 + (obs / 2) * 10;
		Astroid A(obsTexture[obs], blastTexture, renderer, x, -obsSize, obsSize, obsSize, 0, obsSpeed);
		obsList.push_back(A);

		spawnAlert = 0;
	}
	else
	{
		spawnAlert++;
	}

	return;
}

void Obstacle::removeObstacle()
{
	for (int i = 0; i < obsList.size(); i++)
	{
		SDL_Rect dstRect = obsList[i].getdstRect();

		if (dstRect.y > 750 or obsList[i].destructionStatus())
		{
			obsList.erase(obsList.begin() + i);
			i--;
		}
	}

	return;
}

void Obstacle::renderObstacle()
{
	for (int i = 0; i < obsList.size(); i++)
	{
		obsList[i].objRender();
	}

	return;
}

void Obstacle::obstacle()
{
	generateObstacle();
	removeObstacle();
	renderObstacle();
}