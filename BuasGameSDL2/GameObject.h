#pragma once
#include "SDL.h"
#include "TextureManager.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>

class GameObject {
	public:
		GameObject(const std::string & textureSheet, SDL_Renderer* ren, int x, int y);
		GameObject(SDL_Texture * textureSheet, SDL_Renderer* ren, int x, int y);
		~GameObject();
		float scale = 2;
	 	virtual void Update();
		virtual void Render();
		virtual void ProccesInput(int keyCode, bool down);
		virtual void onCollision(std::string tag, GameObject* other);
		virtual void AnimateFrame(int anim);
		int xpos;
		int ypos;
		SDL_Rect srcRect, destRect;
		std::string GetTag();
		std::string tag = "GameObject";
	protected:
		SDL_Texture* objTexture;
		SDL_Texture* testTex;
		SDL_Texture* originTex;
		SDL_Renderer* renderer;
};