#include "EnemyManager.h"

EnemyManager::EnemyManager(SDL_Renderer* ren,std::vector<GameObject*>& gameObjects) : objects(gameObjects)
{
	renderer = ren;
}

EnemyManager::~EnemyManager()  
{

}

void EnemyManager::Update() {
	if (objects.size() < 220) {
	timePassed++;
	if (timePassed >= 20) {
		timePassed = 0;
		for (unsigned int i = 0; i < 10; i++)
		{
			int Random = rand() % 3 + 1;
			// creates all the enemys. 
			if (Random == 3) {
				Enemy * enemy = new Enemy(GameObject("Assets/penguinsBad.png", renderer, 2000, 0));
				enemy->SetEnemyPosScale(i);
				AddGameObjectToObjects(enemy);
				}
			}
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

