#pragma once

#include <SDL.h>
#include "Obstacle.h"
#include "User.h"
#include "Additional.h"

class Collision
{
public :

	Collision(User* player, Obstacle* obs);

	void user_obsCollision();
	void bullet_obsCollision();
	void user_enemyBulletCollision(Enemy* E);
	void checkCollision();

private :

	User* player;
	Obstacle* obs;
};

