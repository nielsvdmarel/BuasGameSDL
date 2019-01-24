#include "Enemy.h"

Enemy::Enemy(GameObject gameObject): GameObject(gameObject) {
	//ypos = rand() % (850 - 50 - 1) + 50;
	scale = 2;
	speed = -2;
	tag = "Enemy";
	// animation parameters, enemy starts walk animation at start and sets the animation as a loop
	beginFrame = 1;
	endFrame = 3;
	loop = true;
	walking = true;
	animationTime = 0;
	randomSpeedInterval = rand() % (randomSpeedMax - randomSpeedMin) + randomSpeedMin;
}

Enemy::~Enemy() {

}

void Enemy::Update() {
	xpos += 1 * speed;
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = (srcRect.w * scale);
	destRect.h = (srcRect.h * scale);
	Animate(beginFrame,endFrame);

	randomSpeedTime++;
	if (randomSpeedTime >= randomSpeedInterval) {
		if (speed == -2) {
			speed = -4;
		}
		else if (speed == -4) {
			speed = -2;
		}
		randomSpeedTime = 0;
		randomSpeedInterval = rand() % (randomSpeedMax - randomSpeedMin) + randomSpeedMin;
	}
}

void Enemy::Animate(int beginFrame, int endFrame)
{
	animationTime++;
	if (animationTime >= animationInterval) {
		if (!cycleDone) {
			currentFrame++;
		}
		if (currentFrame > endFrame) {
			if (loop) {
				currentFrame = beginFrame;
			}
			else if (!loop) {
				currentFrame = endFrame;
				ResetEnemy();
			}
		}
		animationTime %= animationInterval;
		AnimateFrame(currentFrame);
	}
}

void Enemy::ResetEnemy()
{
	xpos = 2000;
	loop = true;
	beginFrame = 1;
	endFrame = 3;
	walking = true;
	int randomy = rand() % 10;
	SetEnemyPosScale(randomy);
}

void Enemy::Render() {
	if (walking) {
		SDL_RenderCopyEx(renderer, objTexture, &srcRect, &destRect, 0, 0, SDL_FLIP_HORIZONTAL);
	}
	else if (!walking) {
		SDL_RenderCopyEx(renderer, objTexture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
	}
}

void Enemy::onCollision(std::string otherTag, GameObject* other)
{
	if (otherTag == "Player") {
		int xposC = xpos + (destRect.w /2);
		int yposC = ypos + (destRect.y /2);
		int otherXposC = other->xpos + (other->destRect.w /2);
		int otherYposC = other->ypos + (other->destRect.h / 2);

		if (abs(otherXposC - xposC) < abs(otherYposC - yposC) + other->destRect.h) {
			if (otherXposC < xposC) {
				other->xpos = (xpos - other->destRect.w);
			} else {
				other->xpos = (xpos + destRect.w);
			}
		} else {
			if (otherYposC < yposC) {
				other->ypos = (ypos - other->destRect.h);
			}
			else {
				other->ypos = (ypos + destRect.h);
			}
		}
	}else if (otherTag == "Enemy") {
		if (other->xpos > xpos) {
			speed = -4;
			//animationInterval = 5; animation update time 
		}

		if (other->xpos < xpos) {
			speed = -2;
			//animationInterval = 10; animation update time
		}
		//std::cout << "collision on enemy from enemy" << std::endl;
	}else if (otherTag == "Wall") {

	}else if (otherTag == "Border") {
		//penguins go underwaters
		beginFrame = 4;
		endFrame = 9;
		loop = false;
		speed = -1;
	}
}

void Enemy::SetEnemyPosScale(int beginYPos)
{
	int Random = rand() % 3 + 1;
	if (Random == 1 || Random == 2) {
		speed = -4;
	} else if (Random == 3) {
		speed = -2;
	}

	int Random2 = rand() % 10 + 1;
	if (Random2 == 4) {
		scale = 3;
	} else if (Random2 != 4){
		scale = 2;
	}

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
		walking = false;
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
	case 9:
		//empty state, use when hiding enemy to reset positions
		srcRect.h = 0;
		srcRect.w = 0;
		srcRect.x = 0;
		srcRect.y = 0;
		break;
	default:

		break;
	}
}


