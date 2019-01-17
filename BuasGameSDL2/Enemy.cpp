#include "Enemy.h"

Enemy::Enemy(GameObject gameObject): GameObject(gameObject) {
	//ypos = rand() % (850 - 50 - 1) + 50;
	scale = 2;
	speed = 2; //rand() % (4 - 1 + 1) + 1;
	tag = "Enemy";
}

Enemy::~Enemy() {

}

void Enemy::Update() {
	xpos -= 1 * speed;
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

void Enemy::onCollision(std::string otherTag, GameObject* other)
{
	if (otherTag == "Player") {
		//std::cout << "collision on player from enemy" << std::endl;
	}else if (otherTag == "Enemy") {
		//std::cout << "collision on enemy from enemy" << std::endl;
	}else if (otherTag == "Wall") {

	}else if (otherTag == "border") {

	}

}

void Enemy::SetEnemyPosScale(int beginYPos)
{
	if (scale <= 2) {
		ypos = 90 + (beginYPos * 90);
	}
	if (scale >= 3) {
		ypos = 25 + (beginYPos * 90);
	}
}
