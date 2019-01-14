#pragma once
#include "GameObject.h"
#include <stdlib.h>
#include <vector>

class Collision {
public:
	Collision(std::vector<GameObject*>& gameObjects);
	~Collision();
	void update();
	bool checkCollision(GameObject * first, GameObject * other);
	void pushBackGameObjects(GameObject * first, GameObject * other);
	void EnemyImpact();
private:
	std::vector<GameObject*>& objects;
};
