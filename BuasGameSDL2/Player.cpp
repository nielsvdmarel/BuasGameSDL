#include "Player.h"
//Creates Player object (GameObject)
Player::Player(GameObject gameObject, Input & i) : GameObject(gameObject), input(i) {
	checkposx = xpos;
	checkposy = ypos;
	speedx = 0;
	speedy = 0;
	tag = "Player";

	srcRect.h = 32;
	srcRect.w = 15;
	srcRect.x = 0;
	srcRect.y = 0;
	alive = true;

	beginFrame = 1;
	endFrame = 3;
	animationTime = 0;
	Animating = false;
}

Player::~Player() {

}

void Player::Animate(int beginFrame, int endFrame) {
	//Aniamte player frames, Depends on selected begin frame and endframe, also loops if the loop bool is true
	if (Animating) {
		animationTime++;
		if (animationTime >= animationInterval) 
				currentFrame++;
			if (currentFrame > endFrame) {
				if (loop) {
					currentFrame = beginFrame;
					Animating = false;
				}
				else if (!loop) {
					currentFrame = endFrame;
				}
			}
		animationTime %= animationInterval;
		//Set actual animation frame
		AnimateFrame(currentFrame);
	}
}

void Player::Update() {
	Animate(beginFrame, endFrame);
	//If wasd is pressed, set animation parameters to walk loop.
	if (alive) {
		if (input.GetKeyDown(4) || input.GetKeyDown(7) || input.GetKeyDown(22) || input.GetKeyDown(26)) {
			loop = true;
			beginFrame = 1;
			endFrame = 3;
			Animating = true;
		}
	}
	//Checks the direction the player is going
	checkDirectionx();
	checkDirectiony();
	//Adds calculated speed to the player
	xpos += speedx * ((input.GetKeyDown(4)) ? -1 : (input.GetKeyDown(7)) ? 1 : DirectionX);
	ypos += speedy * ((input.GetKeyDown(22)) ? 1 : (input.GetKeyDown(26)) ? -1 : DirectionY);
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * scale;
	destRect.h = srcRect.h * scale;
	if (alive) {
		// if A or D is pressed, add or substract speed x smooth
		if (input.GetKeyDown(4) || input.GetKeyDown(7)) {
			if (speedx < 3) {
				speedx += .30f;
			}
			else {
				speedx = 3;
			}
		}
		else {
			if (speedx > 0) {
				speedx -= .08f;
			}
			else if (speedx <= 0) {
				speedx = 0;
			}
		}
		// if W or S is pressed, add or substract speed Y smooth
		if (input.GetKeyDown(22) || input.GetKeyDown(26)) {
			if (speedy < 3) {
				speedy += .30f;
			}
			else {
				speedy = 3;
			}
		}
		else {
			if (speedy > 0) {
				speedy -= .08f;
			}
			else if (speedy <= 0) {
				speedy = 0;
			}
		}
	}
}

void Player::Render() {
	//Renders object
	SDL_RenderCopyEx(renderer, objTexture, &srcRect, &destRect, 0, 0, flip);
	if (alive) {
		if (input.GetKeyDown(4) || DirectionX == -1) {
			flip = SDL_FLIP_HORIZONTAL;
		}
		else
			if (input.GetKeyDown(7) || DirectionX == 1 || !alive) {
				flip = SDL_FLIP_NONE;
			} else {
				flip = SDL_FLIP_NONE;
		}
	}
}

void Player::onCollision(std::string otherTag, GameObject* other) {
	if (otherTag == "Enemy") {
		//Player collided with GameObject with tag "Enemy"
	} else if (otherTag == "Wall") {
		//Player collided with GameObject with tag "Wall"
		int xposC = xpos + (destRect.w / 2);
		int yposC = ypos + (destRect.h / 2);
		int otherXposC = other->xpos + (other->destRect.w / 2);
		int otherYposC = other->ypos + (other->destRect.h / 2);
		//If xpos difference if more then y pos difference, checked to know what axis to push back
		if (abs(otherXposC - xposC) - abs(destRect.w / 2 + other->destRect.w / 2) > abs(otherYposC - yposC) - abs(destRect.h / 2 + other->destRect.h / 2)) {
			if (otherXposC < xposC) {
				xpos = (other->xpos + other->destRect.w);
			}
			else {
				xpos = (other->xpos - destRect.w);
			}
		}
		else {
			if (otherYposC < yposC) {
				ypos = other->ypos + other->destRect.h;
			}
			else {
				ypos = other->ypos - destRect.h;
			}
		}
	} else if (otherTag == "Border") {
		//Player collided with GameObject with tag "Border"
		//Sets movement speeds to 0, Resets image flip, Starts death animation with needed parameters
		if (alive != false) {
			alive = false;
			loop = false;
			beginFrame = 10;
			endFrame = 15;
			currentFrame = beginFrame;
			Animating = true;
			speedx = 3;
			speedy = 0;
			flip = SDL_FLIP_NONE;
		}
	}
}

void Player::checkDirectionx() {
	//checks if checkposx is different from real xpos, result is used to set DirectionX
	if (checkposx > xpos) {
		DirectionX = -1;
	}
	if (checkposx < xpos) {
		DirectionX = 1;
	}

	if (checkposx == xpos) {
		DirectionX = 0;
	}
	checkposx = xpos;
	//std::cout << DirectionX << std::endl;
}

void Player::checkDirectiony() {
	//checks if checkposy is different from real ypos, result is used to set DirectionY
	if (checkposy > ypos) {
		DirectionY = -1;
	}
	if (checkposy < ypos) {
		DirectionY = 1;
	}
	if (checkposy == ypos) {
		DirectionY = 0;
	}
	checkposy = ypos;
	//std::cout << DirectionY << std::endl;
}

void Player::PlayerGameOver() {
	//Turns player off when walked off border, game over
	AnimateFrame(1);
	xpos = -3000;
	ypos = 500;
	speedx = 0;
	speedy = 0;
	loop = false;
	animationTime = 0;
	Animating = false;
	alive = false;
}

void Player::RespawnPlayer() {
	//Respawns player when walked off border, respawn
	ypos = 500;
	xpos = 1000;
	AnimateFrame(1);
	animationTime = 0;
	Animating = false;
	alive = true;
	loop = false;
	speedx = 0;
	speedy = 0;
}

void Player::checkDeathState() {
	if (Started) {
		PlayerGameOver();
		Started = false;
	} else if (!Started) {
		RespawnPlayer();
	}
}

void Player::AnimateFrame(int anim) {
	switch (anim) {
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
		//Normal upward walk cycle (4-5-6)
	case 4:
		srcRect.h = 32;
		srcRect.w = 19;
		srcRect.x = 48;
		srcRect.y = 0;
		break;
	case 5:
		srcRect.h = 32;
		srcRect.w = 17;
		srcRect.x = 68;
		srcRect.y = 0;
		break;
	case 6:
		srcRect.h = 32;
		srcRect.w = 19;
		srcRect.x = 86;
		srcRect.y = 0;
		break;
		//Normal Down walk cycle (7-8-9)
	case 7:
		srcRect.h = 32;
		srcRect.w = 19;
		srcRect.x = 106;
		srcRect.y = 0;
		break;
	case 8:
		srcRect.h = 32;
		srcRect.w = 17;
		srcRect.x = 126;
		srcRect.y = 0;
		break;
	case 9:
		srcRect.h = 32;
		srcRect.w = 19;
		srcRect.x = 144;
		srcRect.y = 0;
		break;
		//Death in water 
	case 10:
		srcRect.h = 32;
		srcRect.w = 23;
		srcRect.x = 164;
		srcRect.y = 0;
		break;
	case 11:
		srcRect.h = 32;
		srcRect.w = 29;
		srcRect.x = 188;
		srcRect.y = 0;
		break;
	case 12:
		srcRect.h = 32;
		srcRect.w = 30;
		srcRect.x = 220;
		srcRect.y = 0;
		break;
	case 13:
		srcRect.h = 32;
		srcRect.w = 19;
		srcRect.x = 253;
		srcRect.y = 0;
		break;
	case 14:
		srcRect.h = 32;
		srcRect.w = 14;
		srcRect.x = 276;
		srcRect.y = 0;
		break;
	case 15:
		srcRect.h = 0;
		srcRect.w = 0;
		srcRect.x = 0;
		srcRect.y = 0;
		//Sets player to game over state, after death animation is at last frame
		checkDeathState();
		break;
	default:
		break;
	}
}


