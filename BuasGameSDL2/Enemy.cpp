#include "Enemy.h"

Enemy::Enemy(GameObject gameObject): GameObject(gameObject) {
	//ypos = rand() % (850 - 50 - 1) + 50;
	scale = rand() % 3 + 1.5;
	speed = rand() % (4 - 1 + 1) + 1;
	tag = "Enemy";
}

Enemy::~Enemy() {

}

void Enemy::Update() {
	//xpos -= 1 * speed;
	srcRect.h = 33;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * scale;
	destRect.h = srcRect.h * scale;
}

void Enemy::Render() {
	SDL_RenderCopyEx(renderer, objTexture, &srcRect, &destRect, 0, 0 ,SDL_FLIP_HORIZONTAL);
}

void Enemy::onCollision(std::string otherTag)
{
	if (otherTag == "Player") {
		std::cout << "collision on player from enemy" << std::endl;
	}

	if (otherTag == "Enemy") {
		//std::cout << "collision on enemy from enemy" << std::endl;
	}
}
