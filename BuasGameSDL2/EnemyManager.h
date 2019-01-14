#pragma once
#include "Enemy.h"
#include "System.h"
#include "GameObject.h"

class EnemyManager: public System {
public:
	EnemyManager(SDL_Renderer* ren, std::vector<GameObject*>& gameObjects);
	~EnemyManager();
	void SpawnEnemyAtRandomYPos();
	void StartWave();
	void CheckEnemyPos();
	void ResetEnemy();
	void Update();
	bool EnemysSpawning;
	SDL_Renderer* renderer;
	void AddGameObjectToObjects(GameObject * gameObject);
private:
	int amountOfEnemys;
	float timePassed;
	float MaxRandomEnemys = 20;
	float minRandomEnemys = 6;
	int maxAmountWaveEnemys;
	int minAmountWaveEnemys;
	std::vector<GameObject*>& objects;
};