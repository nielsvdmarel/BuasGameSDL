#include "EnemyManager.h"

EnemyManager::EnemyManager(SDL_Renderer* ren,std::vector<GameObject*>& gameObjects) : objects(gameObjects)
{
	renderer = ren;
}

EnemyManager::~EnemyManager()  
{

}

void EnemyManager::Update()
{
	timePassed++;
	if (timePassed >= 5) {
		timePassed = 0;
		AddGameObjectToObjects(new Enemy(GameObject("Assets/p22B.png", renderer, 2000, 500)));
	}
}

void EnemyManager::AddGameObjectToObjects(GameObject* gameObject)
{
	objects.push_back(gameObject);
}

void EnemyManager::SpawnEnemyAtRandomYPos()
{
	
}

void EnemyManager::StartWave()
{
	
}

void EnemyManager::CheckEnemyPos()
{

}

void EnemyManager::ResetEnemy()
{
	
}

