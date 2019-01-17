#include "EnemyManager.h"

EnemyManager::EnemyManager(SDL_Renderer* ren,std::vector<GameObject*>& gameObjects) : objects(gameObjects)
{
	renderer = ren;
}

EnemyManager::~EnemyManager()  
{

}

void EnemyManager::Update() {
	timePassed++;
	if (timePassed >= 50) {
		timePassed = 0;
		for (unsigned int i = 0; i < 10; i++)
		{
			Enemy * enemy = new Enemy(GameObject("Assets/p22B.png", renderer, 2000, 0));
			enemy->SetEnemyPosScale(i);
			AddGameObjectToObjects(enemy);
		}
	}
}

void EnemyManager::AddGameObjectToObjects(GameObject* gameObject)
{
	objects.push_back(gameObject);
	//std::cout << objects.size() << std::endl;
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

