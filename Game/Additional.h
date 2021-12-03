#pragma once

#include <SDL_image.h>
#include <SDL.h>

SDL_Texture* loadTexture(const char* assetLocation, SDL_Renderer* renderer);

double objDistance(SDL_Rect rect0, SDL_Rect rect1);