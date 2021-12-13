#pragma once

#include <vector>
#include <SDL_mixer.h>
#include "GameObject.h"
#include "Additional.h"
#include "Gun.h"

class User : public GameObject, public Gun
{
	friend class Collision;

public :

	User(const char* asset1location, const char* asset2location, const char* asset3location, const char* asset4location, const char* asset5location, SDL_Renderer* R, int x, int y, int w, int h, const char* soundLocation, const char* sound2Location, const char* sound3Location);
	~User();

	void handleEvent();
	void eventResponse();
	void objRender();

private :

	const int delVelocity = 6;
	const int  drag = 1;
	const int delGunEnergy = 2;
	const int gunCooldownThresh = 15;
	const SDL_Rect cooldownBarLocation = { 20, 710, 43, 20 };

	int bulletSpeed;
	int bulletListSize;
	int gunEnergy;
	int gunCooldown;

	bool W;
	bool A;
	bool S;
	bool D;
	bool space;

	SDL_Texture* thrustTexture;
	std::vector<SDL_Texture*> cooldownTexture;
};

