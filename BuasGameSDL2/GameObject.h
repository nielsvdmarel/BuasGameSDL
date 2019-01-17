#pragma once
#include "SDL.h"
#include "TextureManager.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>

class GameObject {

	public:
		GameObject(const char * textureSheet, SDL_Renderer* ren, int x, int y);
		~GameObject();
		float scale = 2;
	 	virtual void Update();
		virtual void Render();
		virtual void ProccesInput(int keyCode, bool down);
		virtual void onCollision(std::string tag, GameObject* other);
		int xpos;
		int ypos;
		SDL_Rect srcRect, destRect;
		std::string GetTag();
	protected:
		SDL_Texture* objTexture;
		SDL_Renderer* renderer;
		std::string tag = "GameObject";
		
};