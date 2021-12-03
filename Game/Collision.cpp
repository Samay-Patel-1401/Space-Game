#include "Collision.h"

Collision::Collision(User* player, Obstacle* obs) : player(player), obs(obs)
{
	
}

void Collision::userCollision()
{
	SDL_Rect playerRect = player->getdstRect();
	
	for (int i = 0; i < obs->obsList.size(); i++)
	{
		SDL_Rect obsRect = obs->obsList[i].getdstRect();

		double dst = objDistance(playerRect, obsRect);

		if (dst < (playerRect.w/2 + obsRect.w/2 - 10))
		{
			player->isDestroyed = true;
			obs->obsList[i].destroy();
			return;
		}
	}

	return;
}

void Collision::bulletCollision()
{
	for (int i = 0; i < player->bulletList.size(); i++)
	{
		SDL_Rect bulletRect = player->bulletList[i].getdstRect();

		for (int j = 0; j < obs->obsList.size(); j++)
		{
			SDL_Rect obsRect = obs->obsList[j].getdstRect();

			double dst = objDistance(bulletRect, obsRect);
			if (dst < (bulletRect.w / 2 + obsRect.w / 2 - 5))
			{
				player->bulletList[i].destroy();
				obs->obsList[j].destroy();
			}
		}
	}

	return;
}

void Collision::checkCollision()
{
	userCollision();
	bulletCollision();

	return;
}