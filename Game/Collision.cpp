#include "Collision.h"

Collision::Collision(User* player, Obstacle* obs) : player(player), obs(obs)
{
	
}

void Collision::user_obsCollision()
{
	SDL_Rect playerRect = player->getdstRect();
	
	for (int i = 0; i < obs->astroidList.size(); i++)
	{
		SDL_Rect obsRect = obs->astroidList[i].getdstRect();

		double dst = objDistance(playerRect, obsRect);

		if ((dst < (playerRect.w/2 + obsRect.w/2 - 10)) and !(obs->astroidList[i].status()) and !(player->isDestroyed))
		{
			player->isDestroyed = true;
			obs->astroidList[i].destroy();
			return;
		}
	}

	for (int i = 0; i < obs->enemyList.size(); i++)
	{
		SDL_Rect obsRect = obs->enemyList[i].getdstRect();

		double dst = objDistance(playerRect, obsRect);

		if ((dst < (playerRect.w / 2 + obsRect.w / 2 - 10)) and !(obs->enemyList[i].status()) and !(player->isDestroyed))
		{
			player->isDestroyed = true;
			obs->enemyList[i].destroy();
			return;
		}
	}

	return;
}

void Collision::bullet_obsCollision()
{
	for (int i = 0; i < player->bulletList.size(); i++)
	{
		SDL_Rect bulletRect = player->bulletList[i].getdstRect();

		for (int j = 0; j < obs->astroidList.size(); j++)
		{
			SDL_Rect obsRect = obs->astroidList[j].getdstRect();

			double dst = objDistance(bulletRect, obsRect);
			if ((dst < (bulletRect.w / 2 + obsRect.w / 2)) and !(obs->astroidList[j].status()))
			{
				player->bulletList[i].destroy();
				obs->astroidList[j].destroy();
			}
		}

		for (int j = 0; j < obs->enemyList.size(); j++)
		{
			SDL_Rect obsRect = obs->enemyList[j].getdstRect();

			double dst = objDistance(bulletRect, obsRect);
			if ((dst < (bulletRect.w / 2 + obsRect.w / 2)) and !(obs->enemyList[j].status()))
			{
				player->bulletList[i].destroy();
				obs->enemyList[j].destroy();
			}
		}
	}

	return;
}

void Collision::user_enemyBulletCollision(Enemy* E)
{
	SDL_Rect playerRect = player->getdstRect();

	for (int i = 0; i < E->bulletList.size(); i++)
	{
		SDL_Rect enemyBulletRect = E->bulletList[i].getdstRect();

		double dst = objDistance(playerRect, enemyBulletRect);
		if ((dst < (enemyBulletRect.w / 2 + playerRect.w / 2 - 10)) and !(E->bulletList[i].status()) and !(player->isDestroyed))
		{
			player->isDestroyed = true;
			E->bulletList[i].destroy();
		}
	}

	return;
}

void Collision::checkCollision()
{
	user_obsCollision();
	bullet_obsCollision();

	for (int i = 0; i < obs->enemyList.size(); i++)
	{
		user_enemyBulletCollision(&(obs->enemyList[i]));
	}

	return;
}