#include "GameObject.h"

GameObject::GameObject(const char* textureSheet, SDL_Renderer* ren , int x, int y) {
	renderer = ren;
	objTexture = TextureManager::LoadTexture(textureSheet, ren);
	xpos = x;
	ypos = y;
}

GameObject::~GameObject()
{

}

void GameObject::Update() {

	xpos++;
	ypos++;
	srcRect.h = 33;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * scale;
	destRect.h = srcRect.h * scale;
}

void GameObject::Render() {
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

void GameObject::ProccesInput(int keyCode, bool down)
{

}

void GameObject::onCollision(std::string tag, GameObject* other)
{

}


std::string GameObject::GetTag()
{
	return tag;
}

