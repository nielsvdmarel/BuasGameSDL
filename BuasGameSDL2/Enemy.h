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
	float speed = 4;
	float time;
	float maxTime = 10;
	float currentFrame;
private:

};