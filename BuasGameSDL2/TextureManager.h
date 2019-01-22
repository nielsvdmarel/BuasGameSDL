#pragma once
#include "SDL_image.h"
#include <string>

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const std::string& fileName, SDL_Renderer* ren);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_Renderer* ren);
};