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
#include "Physics.h"
#include "MapColliders.h"
#include "Text.h"

class Game {

public: 
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	void ResetGame();
	Input input;
	EnemyManager* enemyManager;
	bool running() { return isRunning; }
	Map* map;
	MapColliders* mapColliders;
	int DirectionX;
	int DirectionY;
	Collision* collission;
	Text* TitleTxt;
	std::string titleText;
	std::string startGameText;
	std::string goalGameText;
	std::string scoreText;
	Text* GoalText;
	Text* StartGameTxt;
	Text* ScoreTxt;
	Text* ControlsText;
	int score;
	int realScore;
	int textTimer;
	bool OnOffText;
	Player * player;
	bool GameStarted = false;
	bool GameCheck = false;
private:
	int HighScore;
	int cnt = 0;
	bool isRunning = false;
	SDL_Event event;
	std::vector<GameObject*> allGameObjects;
	SDL_Window * window;
	SDL_Renderer * renderer;
};
