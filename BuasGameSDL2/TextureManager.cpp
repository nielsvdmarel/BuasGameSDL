#include "TextureManager.h"
#include <iostream>
SDL_Texture* TextureManager::LoadTexture(const std::string & texture, SDL_Renderer* ren) {
		SDL_Surface* tempSurface = IMG_Load(texture.c_str());
		if (tempSurface == NULL) {
			std::cout << IMG_GetError() << "\n";
		}
		SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
		SDL_FreeSurface(tempSurface);
		return tex;
	
}

void TextureManager::Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest, SDL_Renderer* ren)
{
	if (tex != NULL) {
		SDL_RenderCopy(ren, tex, &src, &dest);
	}
}


