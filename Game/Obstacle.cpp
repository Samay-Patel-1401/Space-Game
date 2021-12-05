#include "Obstacle.h"

Astroid::Astroid(SDL_Texture* asset1Texture, SDL_Texture* asset2Texture, SDL_Renderer* R, int x, int y, int w, int h, int vx, int vy) : GameObject(asset1Texture, asset2Texture, R, x, y, w, h, vx, vy)
{
	explosionSize = 50;
	explosionSizeThresh = 80;
	delExplosion = 1;
}

void Astroid::destroy()
{
	isDestroyed = true;

	return;
}

Enemy::Enemy(SDL_Texture* asset1Texture, SDL_Texture* asset2Texture, SDL_Texture* asset3Texture, SDL_Texture* asset4Texture, SDL_Renderer* R, int x, int y, int w, int h, int vx, int vy) : GameObject(asset1Texture, asset2Texture, R, x, y, w, h, vx, vy), Gun(asset3Texture, asset4Texture, R)
{
	explosionSize = 50;
	explosionSizeThresh = 80;
	delExplosion = 1;

	bulletCooldownThresh = 180;
	bulletSpeed = 50;
}

void Enemy::gunFire(SDL_Rect targetRect)
{
	SDL_Rect enemyRect = getdstRect();

	double vx = (((targetRect.x + targetRect.w / 2 - enemyRect.x - enemyRect.w / 2) * bulletSpeed) / objDistance(targetRect, enemyRect));
	double vy = (((targetRect.y + targetRect.h / 2 - enemyRect.y - enemyRect.h / 2) * bulletSpeed) / objDistance(targetRect, enemyRect));

	if(!isDestroyed)
		shootBullet(bulletTexture, bulletBlastTexture, renderer, enemyRect.x + enemyRect.w / 2, enemyRect.y + enemyRect.h / 2, vx, vy);
	removeBullet();
	renderBullet();

	return;
}

bool Enemy::destructionStatus()
{
	SDL_Rect rect = getdstRect();

	if ((explosionSize > explosionSizeThresh and isDestroyed) and bulletList.size() == 0)
		return true;
	else if ((rect.x < -50 or rect.x > 1000 or rect.y < -50 or rect.y > 750) and bulletList.size() == 0)
		return true;
	else
		return false;
}

void Enemy::destroy()
{
	isDestroyed = true;

	return;
}


Obstacle::Obstacle(SDL_Renderer* R)
{
	obsSpeed = 50;
	renderer = R;
	spawnAlert = 30;

	blastTexture.push_back(loadTexture("Assets/whitePuff12.png", R));
	blastTexture.push_back(loadTexture("Assets/explosion00.png", R));
	blastTexture.push_back(loadTexture("Assets/flash01.png", R));
	obsTexture.push_back(loadTexture("Assets/meteor_detailedSmall.png", R));
	obsTexture.push_back(loadTexture("Assets/meteor_squareDetailedSmall.png", R));
	obsTexture.push_back(loadTexture("Assets/meteor_large.png", R));
	obsTexture.push_back(loadTexture("Assets/meteor_squareLarge.png", R));
	obsTexture.push_back(loadTexture("Assets/meteor_detailedLarge.png", R));
	obsTexture.push_back(loadTexture("Assets/meteor_squareDetailedLarge.png", R));
	obsTexture.push_back(loadTexture("Assets/station_C.png", R));
	obsTexture.push_back(loadTexture("Assets/enemyBullet.png", R));
}

Obstacle::~Obstacle()
{
	for (int i = 0; i < obsTexture.size(); i++)
	{
		SDL_DestroyTexture(obsTexture[i]);
	}

	for (int i = 0; i < blastTexture.size(); i++)
	{
		SDL_DestroyTexture(blastTexture[i]);
	}	
}

void Obstacle::generateObstacle()
{
	if (spawnAlert == spawnTime)
	{
		int obs = (rand() % 7);
		int x = (rand() % 860) + 50;
		if (obs < 6)
		{
			int obsSize = 30 + (obs / 2) * 10;
			Astroid A(obsTexture[obs], blastTexture[0], renderer, x, -obsSize, obsSize, obsSize, 0, obsSpeed);
			astroidList.push_back(A);

			std::cout << astroidList.size() << std::endl;
		}
		else
		{
			Enemy E(obsTexture[6], blastTexture[1], obsTexture[7], blastTexture[2], renderer, x, -40, 40, 40, 0, obsSpeed);
			enemyList.push_back(E);
		}

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
	for (int i = 0; i < astroidList.size(); i++)
	{
		if (astroidList[i].destructionStatus())
		{
			astroidList.erase(astroidList.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < enemyList.size(); i++)
	{
		if (enemyList[i].destructionStatus())
		{
			enemyList.erase(enemyList.begin() + i);
			i--;
		}
	}

	return;
}

void Obstacle::renderObstacle(SDL_Rect userRect)
{
	for (int i = 0; i < astroidList.size(); i++)
	{
		astroidList[i].objRender();
	}

	for (int i = 0; i < enemyList.size(); i++)
	{
		enemyList[i].objRender();
		//enemyList[i].gunFire(userRect);
	}

	return;
}

void Obstacle::obstacle(SDL_Rect userRect)
{
	generateObstacle();
	removeObstacle();
	renderObstacle(userRect);
}