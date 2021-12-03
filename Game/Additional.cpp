#include "Additional.h"

SDL_Texture* loadTexture(const char* assetLocation, SDL_Renderer* renderer)
{
	SDL_Texture* texture;
	SDL_Surface* tmpSurface = IMG_Load(assetLocation);
	texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	return texture;
}

double objDistance(SDL_Rect rect0, SDL_Rect rect1)
{
	double dst = sqrt((rect0.x + rect0.w/2 - rect1.x - rect1.w/2) * (rect0.x + rect0.w / 2 - rect1.x - rect1.w / 2) + (rect0.y + rect0.h/2 - rect1.y - rect1.h/2) * (rect0.y + rect0.h / 2 - rect1.y - rect1.h / 2));

	return dst;
}