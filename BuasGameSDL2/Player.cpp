#include "Player.h"

Player::Player(GameObject gameObject, Input & i) : GameObject(gameObject), input(i) {
	xpos = 200;
	checkposx = xpos;
	ypos = 580;
	checkposy = ypos;
	speedx = 0;
	speedy = 0;
}

Player::~Player()
{

}

void Player::Update() {
	checkDirectionx();
	checkDirectiony();
	xpos += speedx * ((input.GetKeyDown(4)) ? -1 : (input.GetKeyDown(7)) ? 1 : DirectionX);
	ypos += speedy * ((input.GetKeyDown(22)) ? 1 : (input.GetKeyDown(26)) ? -1 : DirectionY);
	srcRect.h = 33;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;
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
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

void Player::onCollision(std::string tag)
{
	if (tag == "Player") {
		//player behaviour
	}

	if (tag == "Enemy") {
		//enemy behaviour
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
		std::cout << DirectionX << std::endl;
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
		std::cout << DirectionY << std::endl;
	
}


