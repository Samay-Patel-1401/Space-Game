#include "User.h"

User::User(const char* asset1location, const char* asset2location, const char* asset3location, const char* asset4location, const char* asset5location, SDL_Renderer* R, int x, int y, int w, int h, const char* sound1Location, const char* sound2Location, const char* sound3Location) : GameObject(asset1location, asset3location,R, x, y, w, h, 0, 0, sound1Location), Gun(asset4location, asset5location, R, sound2Location, sound3Location)
{
	thrustTexture = loadTexture(asset2location, R);
	blastTexture = loadTexture(asset3location, R);

	W = false; A = false; D = false; S = false; space = false;
	isDestroyed = false;

	explosionSize = 10;
	explosionSizeThresh = 100;
	delExplosion = 2;

	bulletSpeed = -160;
	bulletCooldownThresh = 5;
	bulletCooldown = bulletCooldownThresh;
	bulletListSize = bulletList.size();

	gunEnergy = 20;
	gunCooldown = 0;

	char cooldownAssetLocation[31];
	for (int i = 0; i < 21; i++)
	{
		sprintf_s(cooldownAssetLocation, "Assets/cooldown/cooldown%d.png", i);
		cooldownTexture.push_back(loadTexture(cooldownAssetLocation, R));
	}
}

User::~User()
{
	clean();
	cleanGun();
	SDL_DestroyTexture(thrustTexture);
	for (int i = 0; i < 21; i++)
	{
		SDL_DestroyTexture(cooldownTexture[i]);
	}
}

void User::handleEvent()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	W = state[SDL_SCANCODE_W];
	A = state[SDL_SCANCODE_A];
	S = state[SDL_SCANCODE_S];
	D = state[SDL_SCANCODE_D];
	space = state[SDL_SCANCODE_SPACE];

	eventResponse();

	return;
}

void User::eventResponse()
{
	if (velocity[0] < 60 and D)
		velocity[0] += delVelocity;
	if (velocity[0] > -60 and A)
		velocity[0] -= delVelocity;
	
	if (velocity[1] < 60 and S)
		velocity[1] += delVelocity;
	if (velocity[1] > -60 and W)
		velocity[1] -= delVelocity;
	
	if (velocity[0] > 0)
		velocity[0] -= drag;
	else if (velocity[0] < 0)
		velocity[0] += drag;

	if (velocity[1] > 0)
		velocity[1] -= drag;
	else if (velocity[1] < 0)
		velocity[1] += drag;

	if (space and !isDestroyed and (gunEnergy >= 2))
	{
		bulletListSize = bulletList.size();

		shootBullet(bulletTexture, bulletBlastTexture, renderer, getdstRect().x + getdstRect().w / 2, getdstRect().y, 0, bulletSpeed);

		if (bulletList.size() > bulletListSize)
			gunEnergy -= delGunEnergy;
	}
	else
	{
		gunCooldown++;
		if (gunCooldown == gunCooldownThresh)
		{
			gunCooldown = 0;

			if(gunEnergy < 20)
				gunEnergy++;
		}
	}

	return;
}

void User::objRender()
{
	if (isDestroyed)
	{
		onExplosion();
	}
	else
	{
		SDL_Rect* dstRect = updateGameObject();

		if (W or A or S or D)
		{
			dstRect->y += 30;
			SDL_RenderCopy(renderer, thrustTexture, nullptr, dstRect);
			dstRect->y -= 30;
		}
		SDL_RenderCopy(renderer, objTexture, nullptr, dstRect);
		SDL_RenderCopy(renderer, cooldownTexture[gunEnergy], nullptr, &cooldownBarLocation);
	}

	removeBullet();
	renderBullet();

	return;
}