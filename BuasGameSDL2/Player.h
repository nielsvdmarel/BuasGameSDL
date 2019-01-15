#pragma once
#include "GameObject.h"
#include "Input.h"

class Player:public GameObject {

public:
	Player(GameObject gameObject, Input & i);
	~Player();
	Input & input;
	float scale = 2;
	void Update();
	void Render();
	void onCollision(std::string otherTag);
	void checkDirectionx();
	void checkDirectiony();
	int DirectionY;
	int DirectionX;
	float speedx;
	float speedy;
	float checkposx;
	float checkposy;
};