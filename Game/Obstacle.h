#pragma once

#include <SDL.h>
#include <vector>
#include "GameObject.h"
#include "Gun.h"

class Astroid : public GameObject
{
public :

	Astroid(SDL_Texture* asset1Texture, SDL_Texture* asset2Texture, SDL_Renderer* R, int x, int y, int w, int h, int vx, int vy);

	void destroy();
};

class Enemy : public GameObject, public Gun
{
public :

	Enemy(SDL_Texture* asset1Texture, SDL_Texture* asset2Texture, SDL_Texture* asset3Texture, SDL_Texture* asset4Texture, SDL_Renderer* R, int x, int y, int w, int h, int vx, int vy);

	void gunFire(SDL_Rect targetRect);
	bool destructionStatus();
	void destroy();

private :

	int bulletSpeed;
};

class Obstacle
{
	friend class Collision;

public :

	Obstacle(SDL_Renderer* R);
	~Obstacle();

	void generateObstacle();
	void removeObstacle();
	void renderObstacle(SDL_Rect userRect);
	void obstacle(SDL_Rect userRect);

private :

	std::vector<Astroid> astroidList;
	std::vector<Enemy> enemyList;

	int spawnAlert;
	int obsSpeed;
	const int spawnTime = 60;

	std::vector<SDL_Texture*> obsTexture;
	std::vector<SDL_Texture*> blastTexture;
	SDL_Renderer* renderer;
};

