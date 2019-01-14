#include "Physics.h"

Collision::Collision(std::vector<GameObject*>& gameObjects) : objects(gameObjects)
{
	 
}

Collision::~Collision()
{

}

void Collision::update()
{
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		for (unsigned int j = i + 1; j < objects.size(); j++)
		{
			objects[i]->onCollision(objects[j]->GetTag());
			objects[j]->onCollision(objects[i]->GetTag()); 
		}
	}
}

bool Collision::checkCollision(GameObject * first, GameObject * other)
{
	return false;
}

void Collision::pushBackGameObjects(GameObject * first, GameObject * other)
{

}

void Collision::EnemyImpact()
{

}
