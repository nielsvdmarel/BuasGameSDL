#pragma once
#include "GameObject.h"

class Enemy :public GameObject {

public:
	Enemy(GameObject gameObject);
	~Enemy();
	float scale;
	void Update() override;
	void Render() override;
	void onCollision(std::string otherTag, GameObject* other);
	void SetEnemyPosScale(int beginYPos);
	void AnimateFrame(int Anim);
	void Animate(int beginFrame, int endFrame);
	int speed = 4;
	float time;
	float animationInterval = 10;
	float currentFrame;
private:
	bool walking;
	int beginFrame = 1;
	int endFrame = 3;
	bool loop;
	bool cycleDone;
};