#pragma once

#include <vector>
#include "GameObject.h"
#include "Additional.h"
#include "Gun.h"

class User : public GameObject, public Gun
{
	friend class Collision;

public :

	User(const char* asset1location, const char* asset2location, const char* asset3location, const char* asset4location, const char* asset5location, SDL_Renderer* R, int x, int y, int w, int h);
	~User();

	void handleEvent();
	void eventResponse();
	void objRender();

private :

	const int delVelocity = 6;
	const int  drag = 1;

	int bulletSpeed;

	bool W;
	bool A;
	bool S;
	bool D;
	bool space;

	SDL_Texture* thrustTexture;
};

