#pragma once
#include "GameObject.h"
#include <iostream>
#include "Input.h"

class Player:public GameObject {

public:
	Player(GameObject gameObject, Input & i);
	~Player();
	Input & input;
	float scale = 2;
	void Update();
	void Render();
	void onCollision(std::string tag);
	void checkDirectionx();
	void checkDirectiony();
	int DirectionY;
	int DirectionX;
	float speedx;
	float speedy;
	float checkposx;
	float checkposy;
	std::string tag = "Player";
private:
	int xpos;
	int ypos;
};