#include "Enemy.h"

Enemy::Enemy(GameObject gameObject): GameObject(gameObject) {
	//ypos = rand() % (850 - 50 - 1) + 50;
	scale = 2;
	speed = -3;
	tag = "Enemy";
	// animation parameters, enemy starts walk animation at start and sets the animation as a loop
	beginFrame = 1;
	endFrame = 3;
	loop = true;
	walking = true;
	animationTime = 0;
	// creates random speed value for random speed transitions
	randomSpeedInterval = rand() % (randomSpeedMax - randomSpeedMin) + randomSpeedMin;
}

Enemy::~Enemy() {
	
}

void Enemy::Update() {
	// makes enemy always move with it's speed variable
	xpos += 1 * speed;
	destRect.x = xpos;
	destRect.y = ypos;
	// width and height variables, used for collision
	destRect.w = (srcRect.w * scale);
	destRect.h = (srcRect.h * scale);
	//Enemy always animates
	Animate(beginFrame,endFrame);

	//Frame timer for speed transition
	randomSpeedTime++;
	if (randomSpeedTime >= randomSpeedInterval) {
		if (speed == -3) {
			speed = -5;
		}
		else if (speed == -5) {
			speed = -3;
		}
		randomSpeedTime = 0;
		randomSpeedInterval = rand() % (randomSpeedMax - randomSpeedMin) + randomSpeedMin;
	}
}

void Enemy::Animate(int beginFrame, int endFrame)
{
	//Frame animation timer, used for changing the current animation(frame)
	animationTime++;
	if (animationTime >= animationInterval) {
			currentFrame++;
		if (currentFrame > endFrame) {
			if (loop) {
				currentFrame = beginFrame;
			}
			else if (!loop) {
				currentFrame = endFrame;
				if (Started) {
				 ResetEnemy();
				}
			}
		}
		animationTime %= animationInterval;
		AnimateFrame(currentFrame);
	}
}

void Enemy::ResetEnemy() {
	//Enemy xpos position reset
	xpos = 2000;
	//Animation reset
	loop = true;
	beginFrame = 1;
	endFrame = 3;
	walking = true;
	//New random y pos
	int randomy = rand() % 10;
	SetEnemyPosScale(randomy);
}

void Enemy::Render() {
	if (walking) {
		//Flip enemy when walking
		SDL_RenderCopyEx(renderer, objTexture, &srcRect, &destRect, 0, 0, SDL_FLIP_HORIZONTAL);
	}
	else if (!walking) {
		//None flip enemy when jumping in the water/ not walking
		SDL_RenderCopyEx(renderer, objTexture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
	}
}

//Collision response
void Enemy::onCollision(std::string otherTag, GameObject* other) {
	//checks if other object has tag "Player"
	if (otherTag == "Player") {
		//SDL calculates position from left corner, we need midle pos
		int xposC = xpos + (destRect.w /2);
		int yposC = ypos + (destRect.y /2);
		int otherXposC = other->xpos + (other->destRect.w /2);
		int otherYposC = other->ypos + (other->destRect.h / 2);
		//checks if x difference is smaller then y difference (enemy and other object)
		if (abs(otherXposC - xposC) < abs(otherYposC - yposC) + other->destRect.h) {
			if (otherXposC < xposC) {
				// moves right
				other->xpos = (xpos - other->destRect.w);
			} else {
				//moves left
				other->xpos = (xpos + destRect.w);
			}
		} else {
			if (otherYposC < yposC) {
				//moves up
				other->ypos = (ypos - other->destRect.h);
			} else {
				//moves down
				other->ypos = (ypos + destRect.h);
			}
		}
		//checks if other object has tag "Enemy"
	} else if (otherTag == "Enemy") {
		//if other enemy xpos is bigger (further to the right) increase own speed
		if (other->xpos > xpos) {
			speed = -5;
			animationInterval = 5;// animation update time 
		}
		//if other enemy xpos is smaller (further to the left) slow down own speed
		if (other->xpos < xpos) {
			speed = -3;
			animationInterval = 10;// animation update time
		}
	} else if (otherTag == "Border") {
		//penguins go underwaters
		animationInterval = 10;
		beginFrame = 4;
		endFrame = 9;
		loop = false;
		speed = -1;
	}
}

void Enemy::SetEnemyPosScale(int beginYPos)
{
	//creates random number to use for scale
	int Random = rand() % 3 + 1;
	if (Random == 1 || Random == 2) {
		speed = -5;
	} else if (Random == 3) {
		speed = -3;
	}

	int Random2 = rand() % 10 + 1;
	if (Random2 == 4) {
		scale = 3;
	} else if (Random2 != 4){
		scale = 2;
	}

	if (scale <= 2) {
		//Sets ypos calculation with scale.
		ypos = 90 + (beginYPos * 90);
	}
	if (scale >= 3) {
		//Sets ypos calculation with scale.
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


