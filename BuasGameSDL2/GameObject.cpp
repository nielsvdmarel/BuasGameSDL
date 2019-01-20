#include "GameObject.h"

GameObject::GameObject(const char* textureSheet, SDL_Renderer* ren , int x, int y) {
	renderer = ren;
	objTexture = TextureManager::LoadTexture(textureSheet, ren);
	xpos = x;
	ypos = y;


	//dit zat in de update
	srcRect.w = 33;
	srcRect.h = 32;
	srcRect.x = 0;
	srcRect.y = 0;
}

GameObject::~GameObject()
{

}

void GameObject::Update() {

	xpos++;
	ypos++;

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

void GameObject::AnimateFrame(int anim)
{

}

std::string GameObject::GetTag()
{
	return tag;
}

