#pragma once
#include "GameObject.h"

class Enemy :public GameObject {

public:
	Enemy(GameObject gameObject);
	~Enemy();
	float scale;
	void Update() override;
	void Render() override;
	void onCollision(std::string tag);
	int velocity;
	float speed = 4;
	int EnemyXpos;
	int EnemyYpos;
	std::string tag  = "Enemy";
private:

};