 #include "EnemyManager.h"

EnemyManager::EnemyManager(SDL_Renderer* ren,bool& gameStarted ,std::vector<GameObject*>& gameObjects): objects(gameObjects), started(gameStarted) {
	renderer = ren;
	SpawnAllEnemys();
}

EnemyManager::~EnemyManager() {
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

void EnemyManager::AddGameObjectToObjects(GameObject* gameObject) {
	objects.push_back(gameObject);
}

void EnemyManager::AddGameObjectToEnemys(GameObject * gameObject) {
	enemys.push_back(gameObject);
	std::cout << " enemys count: " + std::to_string(enemys.size()) << std::endl;
}

void EnemyManager::SpawnAllEnemys() {
	for (unsigned int i = 0; i < totalEnemys; i++) {
		Enemy * enemy = new Enemy(GameObject("Assets/penguinsBad.png", renderer, 2000, 0, started));
		AddGameObjectToEnemys(enemy);
		AddGameObjectToObjects(enemy);
		enemiesStack.push(enemy);
	}
	RePlaceAllEnemys();
}

void EnemyManager::RePlaceAllEnemys() {
	while (enemiesStack.size() != NULL){
		for (unsigned int i = 0; i < 10; i++) {
			int Random = rand() % 3 + 1;
			if (Random = 3) {
				enemiesStack.top()->SetEnemyPosScale(i);
				enemiesStack.top()->xpos = xStartPos;
				enemiesStack.pop();
			}
		}
		xStartPos += 150;
	}
}

