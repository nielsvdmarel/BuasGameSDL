#include "Player.h"

Player::Player(GameObject gameObject, Input & i) : GameObject(gameObject), input(i) {
	checkposx = xpos;
	checkposy = ypos;
	speedx = 0;
	speedy = 0;
	tag = "Player";

	//dit zat in de update
	srcRect.h = 32;
	srcRect.w = 15;
	srcRect.x = 0;
	srcRect.y = 0;
}

Player::~Player()
{

}

void Player::Update() {

	if (input.GetKeyDown(4) || input.GetKeyDown(7)|| input.GetKeyDown(22)|| input.GetKeyDown(26)) {
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
	
	checkDirectionx();
	checkDirectiony();
	xpos += speedx * ((input.GetKeyDown(4)) ? -1 : (input.GetKeyDown(7)) ? 1 : DirectionX);
	ypos += speedy * ((input.GetKeyDown(22)) ? 1 : (input.GetKeyDown(26)) ? -1 : DirectionY);
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * scale;
	destRect.h = srcRect.h * scale;
	//std::cout << speed << std::endl;
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
		else if (speedx <= 0){
			speedx = 0;
		}
	}

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

void Player::Render() {
	
	if (input.GetKeyDown(4) || DirectionX == -1) {
		SDL_RenderCopyEx(renderer, objTexture, &srcRect, &destRect, 0, 0,  SDL_FLIP_HORIZONTAL);
	} else
	if (input.GetKeyDown(7) || DirectionX == 1) {
		SDL_RenderCopyEx(renderer, objTexture, &srcRect, &destRect ,0 , 0, SDL_FLIP_NONE);
	}
	else {
		SDL_RenderCopyEx(renderer, objTexture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
	}
	
	//SDL_RenderCopyEx(renderer, objTexture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void Player::onCollision(std::string otherTag, GameObject* other)
{
	
	if (otherTag == "Enemy") {
	
		//std::cout << "PLAYER TOUCHED A ENEMY" << std::endl;
	} else if (otherTag == "Wall") {

		int xposC = xpos + (destRect.w / 2);
		int yposC = ypos + (destRect.h / 2);
		int otherXposC = other->xpos + (other->destRect.w / 2);
		int otherYposC = other->ypos + (other->destRect.h / 2);

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
		// check enemy death animation sequence, but exit game sequence needed. 
	}
}

void Player::checkDirectionx()
{
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

void Player::checkDirectiony()
{
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

void Player::AnimateFrame(int anim)
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
		srcRect.x = 32 ;
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
		break;
	default:
		
		break;
	}
}


