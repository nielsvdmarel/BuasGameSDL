 #pragma once
#include "Enemy.h"
#include "System.h"
#include "GameObject.h"
#include "Player.h"
#include <stack>

class EnemyManager: public System {
public:
	EnemyManager(SDL_Renderer* ren, bool& gameStarted, std::vector<GameObject*>& gameObjects);
	~EnemyManager();
	void Update();
	bool EnemysSpawning;
	SDL_Renderer* renderer;
	void AddGameObjectToObjects(GameObject * gameObject);
	void AddAllEnemysToStack();
	void SpawnAllEnemys();
	void RePlaceAllEnemys();
private:
	int totalEnemys = 110;
	int xStartPos = 2000;
	int RespawnXDistance;
	int amountOfEnemys;
	float timePassed;
	float MaxRandomEnemys = 20;
	float minRandomEnemys = 6;
	int maxAmountWaveEnemys;
	int minAmountWaveEnemys;
	bool& started;
	std::vector<GameObject*>& objects;
	std::vector<Enemy*> allEnemies;
	std::stack<Enemy*> enemiesStack;
};