#pragma once

#include "SDL.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include <iostream>
#include <string>
#include "Enemy.h"
#include "Input.h"
#include "Player.h"
#include <time.h>
#include "System.h"
#include "EnemyManager.h"

class Game {

public: 
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	Input input;
	EnemyManager* enemyManager;
	bool running() { return isRunning; }
	Map* map;
	int DirectionX;
	int DirectionY;
	

private:
	int cnt = 0;
	bool isRunning = false;
	SDL_Event event;
	std::vector<GameObject*> allGameObjects;
	SDL_Window * window;
	SDL_Renderer * renderer;
};
