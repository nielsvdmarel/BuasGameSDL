#pragma once
#include "GameObject.h"
#include <stdlib.h>
#include <vector>

class Collision {
public:
	Collision(std::vector<GameObject*>& gameObjects);
	~Collision();
	void update();
private:
	std::vector<GameObject*>& objects;
};
