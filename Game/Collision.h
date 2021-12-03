#pragma once

#include <SDL.h>
#include "Obstacle.h"
#include "User.h"
#include "Additional.h"

class Collision
{
public :

	Collision(User* player, Obstacle* obs);

	void userCollision();
	void bulletCollision();
	void checkCollision();

private :

	User* player;
	Obstacle* obs;
};

