#include "EnemyManager.h"

EnemyManager::EnemyManager(SDL_Renderer* ren,bool& gameStarted ,std::vector<GameObject*>& gameObjects): objects(gameObjects), started(gameStarted)
{
	renderer = ren;
}

EnemyManager::~EnemyManager()  
{
	SDL_DestroyRenderer(renderer);
}

void EnemyManager::Update() {
	//Checks how many objects are already created
	if (objects.size() < 220) {
	timePassed++;
	//Delay for spawning all enemy's
	if (timePassed >= 20) {
		timePassed = 0;
		//Randomly creates enemy's y position
		for (unsigned int i = 0; i < 10; i++)
		{
			int Random = rand() % 3 + 1;
			// creates all the enemys and places them with frames delay and random positions
			if (Random == 3) {
				Enemy * enemy = new Enemy(GameObject("Assets/penguinsBad.png", renderer, 2000, 0, started));
				enemy->SetEnemyPosScale(i);
				AddGameObjectToEnemys(enemy);
				AddGameObjectToObjects(enemy);
				}
			}
		}
	}
}

void EnemyManager::AddGameObjectToObjects(GameObject* gameObject)
{
	objects.push_back(gameObject);
}

void EnemyManager::AddGameObjectToEnemys(GameObject * gameObject)
{
	enemys.push_back(gameObject);
}

