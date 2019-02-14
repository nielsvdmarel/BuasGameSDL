 #include "EnemyManager.h"

EnemyManager::EnemyManager(SDL_Renderer* ren,bool& gameStarted ,std::vector<GameObject*>& gameObjects): objects(gameObjects), started(gameStarted) {
	renderer = ren;
	SpawnAllEnemys();
}

EnemyManager::~EnemyManager() {
	SDL_DestroyRenderer(renderer);
}


void EnemyManager::Update() {
	//EnemyManager update
}

void EnemyManager::AddGameObjectToObjects(GameObject* gameObject) {
	objects.push_back(gameObject);
}

void EnemyManager::SpawnAllEnemys() {
	for (unsigned int i = 0; i < totalEnemys; i++) {
		Enemy * enemy = new Enemy(GameObject("Assets/penguinsBad.png", renderer, 2000, 0, started));
		AddGameObjectToObjects(enemy);
		allEnemies.push_back(enemy);
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
	AddAllEnemysToStack();
	xStartPos = 2000;
}

void EnemyManager::AddAllEnemysToStack() {
	for (unsigned int i = 0; i < allEnemies.size(); i++) {
		enemiesStack.push(allEnemies[i]);
	}
}

