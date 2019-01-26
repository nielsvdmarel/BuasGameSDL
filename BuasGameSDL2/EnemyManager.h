#pragma once
#include "Enemy.h"
#include "System.h"
#include "GameObject.h"
#include "Player.h"

class EnemyManager: public System {
public:
	EnemyManager(SDL_Renderer* ren, bool& gameStarted, std::vector<GameObject*>& gameObjects);
	~EnemyManager();
	void Update();
	bool EnemysSpawning;
	SDL_Renderer* renderer;
	void AddGameObjectToObjects(GameObject * gameObject);
	void AddGameObjectToEnemys(GameObject* gameObject);
private:
	int RespawnXDistance;
	int amountOfEnemys;
	float timePassed;
	float MaxRandomEnemys = 20;
	float minRandomEnemys = 6;
	int maxAmountWaveEnemys;
	int minAmountWaveEnemys;
	bool& started;
	std::vector<GameObject*>& objects;
	std::vector<GameObject*> enemys;
};