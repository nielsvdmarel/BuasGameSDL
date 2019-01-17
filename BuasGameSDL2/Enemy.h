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
	int velocity;
	float speed = 4;
private:

};