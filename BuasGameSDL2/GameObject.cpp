#include "GameObject.h"
//Gameobject base script
GameObject::GameObject(const std::string & textureSheet, SDL_Renderer* ren , int x, int y, bool& gameStarted) : Started(gameStarted) {
	renderer = ren;
	objTexture = TextureManager::LoadTexture(textureSheet, ren);
	xpos = x;
	ypos = y;
	srcRect.h = 24;
	srcRect.w = 24;
	srcRect.x = 0;
	srcRect.y = 0;
}

GameObject::GameObject(SDL_Texture* textureSheet, SDL_Renderer* ren, int x, int y, bool& gameStarted): Started(gameStarted) {
	renderer = ren;
	objTexture = textureSheet;
	xpos = x;
	ypos = y;
	srcRect.h = 24;
	srcRect.w = 24;
	srcRect.x = 0;
	srcRect.y = 0;
}

GameObject::~GameObject()
{

}

void GameObject::Update() {
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * scale;
	destRect.h = srcRect.h * scale;
}

void GameObject::Render() {
	if (objTexture) {
		SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
	}
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

