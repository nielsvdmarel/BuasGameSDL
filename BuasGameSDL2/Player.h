#pragma once
#include "GameObject.h"
#include "Input.h"

class Player:public GameObject {

public:
	Player(GameObject gameObject, Input & i);
	~Player();
	Input & input;
	int scale = 2;
	void Update();
	void Render();
	void onCollision(std::string otherTag, GameObject* other);
	void Animate(int beginFrame, int endFrame);
	void checkDirectionx();
	void checkDirectiony();
	void PlayerGameOver();
	void RespawnPlayer();
	void checkDeathState();
	int DirectionY;
	int DirectionX;
	float speedx;
	float speedy;
	int checkposx;
	int checkposy; 
	void AnimateFrame(int anim);
	int currentFrame;
	int animationTime;
	int animationInterval = 7;
	bool alive;
private:
	bool Animating;
	int beginFrame;
	int endFrame;
	bool loop;
	bool cycleDone;
	SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
};