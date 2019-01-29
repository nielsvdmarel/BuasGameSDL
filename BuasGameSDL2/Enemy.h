#pragma once
#include "GameObject.h"

class Enemy :public GameObject {

public:
	Enemy(GameObject gameObject);
	~Enemy();
	int scale;
	void Update() override;
	void Render() override;
	void onCollision(std::string otherTag, GameObject* other);
	void SetEnemyPosScale(int beginYPos);
	void AnimateFrame(int Anim);
	void Animate(int beginFrame, int endFrame);
	void ResetEnemy();
	int speed = 4;
	int animationTime;
	int animationInterval = 10;
	int currentFrame;
	int randomSpeedTime;
	int randomSpeedInterval;
	int randomSpeedMin = 100;
	int randomSpeedMax = 200;
private:
	bool walking;
	int beginFrame = 1;
	int endFrame = 3;
	bool loop;
};