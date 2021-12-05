#include "Game.h"
#include "GameObject.h"
#include "User.h"
#include "Obstacle.h"
#include "Collision.h"

int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Game game;
	game.initWindow("The Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 750, false);

	SDL_Texture* bgTexture = loadTexture("Assets/BG.png", game.getRenderer());

	User player("Assets/ship_G.png", "Assets/effect_yellow.png", "Assets/explosion00.png", "Assets/bullet.png", "Assets/flash01.png", game.getRenderer(), 480, 600, 40, 40);
	Obstacle obs(game.getRenderer());
	Collision collision(&player, &obs);

	int startTime, frameTime;

	while (game.status())
	{
		startTime = SDL_GetTicks();

		game.handleEvent();
		player.handleEvent();

		SDL_RenderClear(game.getRenderer());

		SDL_RenderCopy(game.getRenderer(), bgTexture, nullptr, nullptr);
		obs.obstacle(player.getdstRect());
		player.objRender();

		SDL_RenderPresent(game.getRenderer());

		collision.checkCollision();

		frameTime = SDL_GetTicks() - startTime;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	SDL_DestroyTexture(bgTexture);

	std::cout << "Game Loop Exited...." << std::endl;

	return 0;
}