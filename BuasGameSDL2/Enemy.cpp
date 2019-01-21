#include "Enemy.h"

Enemy::Enemy(GameObject gameObject): GameObject(gameObject) {
	//ypos = rand() % (850 - 50 - 1) + 50;
	scale = 2;
	speed = -2;
	tag = "Enemy";
	testTex = TextureManager::LoadTexture("Assets / p21.png", renderer);


	// dit zat in de update
	srcRect.h = 32;
	srcRect.w = 15;
	srcRect.x = 0;
	srcRect.y = 0;
}

Enemy::~Enemy() {

}

void Enemy::Update() {
	xpos += 1 * speed;
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * scale;
	destRect.h = srcRect.h * scale;

	time++;
	if (time >= maxTime) {
		currentFrame++;
		time = 0;
		AnimateFrame(currentFrame);
		if (currentFrame > 2) {
			currentFrame = 0;
		}
	}
}

void Enemy::Render() {
	SDL_RenderCopyEx(renderer, objTexture, &srcRect, &destRect, 0, 0 ,SDL_FLIP_HORIZONTAL);
}

void Enemy::onCollision(std::string otherTag, GameObject* other)
{
	if (otherTag == "Player") {
		//std::cout << "collision on player from enemy" << std::endl;
		//objTexture = TextureManager::LoadTexture("Assets/p21.png", renderer); // TO TEST with

		other->xpos += speed;

	}else if (otherTag == "Enemy") {
		if (other->xpos > xpos) {
			speed = -4;
		}

		if (other->xpos < xpos) {
			speed = -2;
		}
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

void Enemy::AnimateFrame(int anim)
{
	switch (anim)
	{
		//Normal walk cycle (1-2-3), can be inverted for left direction
	case 1:
		srcRect.h = 32;
		srcRect.w = 15;
		srcRect.x = 0;
		srcRect.y = 0;
		break;
	case 2:
		srcRect.h = 32;
		srcRect.w = 15;
		srcRect.x = 16;
		srcRect.y = 0;
		break;
	case 3:
		srcRect.h = 32;
		srcRect.w = 15;
		srcRect.x = 32;
		srcRect.y = 0;
		break;
		//Death in water 
	case 4:
		srcRect.h = 32;
		srcRect.w = 23;
		srcRect.x = 164;
		srcRect.y = 0;
		break;
	case 5:
		srcRect.h = 32;
		srcRect.w = 29;
		srcRect.x = 188;
		srcRect.y = 0;
		break;
	case 6:
		srcRect.h = 32;
		srcRect.w = 30;
		srcRect.x = 220;
		srcRect.y = 0;
		break;
	case 7:
		srcRect.h = 32;
		srcRect.w = 19;
		srcRect.x = 253;
		srcRect.y = 0;
		break;
	case 8:
		srcRect.h = 32;
		srcRect.w = 14;
		srcRect.x = 276;
		srcRect.y = 0;
		break;
	default:

		break;
	}
}

