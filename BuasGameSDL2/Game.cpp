#include "Game.h"

Game::Game() {
	TTF_Init();
	GameStarted = false;
}
Game::~Game() {
	for (unsigned int i = 0; i < allGameObjects.size(); i++) {
		delete allGameObjects[i];
		//This includes player
		//This includes map colliders
		//This includes enemys
	}
	delete enemyManager;
	delete map;
	delete mapColliders;
	delete collission;
	delete TitleTxt;
	delete GoalText;
	delete StartGameTxt;
	delete ScoreTxt;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	// this function is called when destructed
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
	//Sets new random on time
	srand(time(NULL));
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "subsystems initialised!..." << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "window created" << std::endl; 
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer created" << std::endl;
		}
		isRunning = true; 
	}

	//Creates new map and assign deafult number to vector
	map = new Map(renderer);
	//Reads map file, import text to map vector, spawn tiles 
	map->ParseMap("Assets/Map.txt");
	// Creates map colliders object
	mapColliders = new MapColliders(renderer, GameStarted, allGameObjects);
	//Reads map colliders file to fill in vector
	mapColliders->ParseMap("Assets/CollisionMap.txt");
	//Creates actual colliders based on new vector data
	mapColliders->CreateMapColliders();
	//New enemymanager object created
	enemyManager = new EnemyManager(renderer, GameStarted, allGameObjects);
	//New player object created
	player = new Player(GameObject("Assets/penguins.png", renderer, 1000, 500, GameStarted), input);
	allGameObjects.push_back(player);
	// Collision(system) object created
	collission = new Collision(allGameObjects);
	//Title text created
	TitleTxt = new Text("Assets/SuperMario256.ttf", 120, "Pushy Penguins!", {144, 144, 144, 144 }, renderer);
	//Instruction text created
	startGameText = "Press space to start!";
	StartGameTxt = new Text("Assets/SuperMario256.ttf", 60, startGameText, { 105, 105, 105, 255 }, renderer);
	//Creates the text that explains the goal of the games
	goalGameText = "Don't get pushed off the icy snow!";
	GoalText = new Text("Assets/SuperMario256.ttf", 50, goalGameText, { 144, 144, 144, 144 }, renderer);
	//Creates the text that shows the current highScore
	scoreText = "HighScore: " + std::to_string(HighScore);
	//ScoreTxt = new Text("Assets/SuperMario256.ttf", 70, scoreText, { 105, 105, 105, 255 }, renderer);
	ControlsText = new Text("Assets/SuperMario256.ttf", 55, "Use WASD to move", { 105, 105, 105, 255 }, renderer);
}

void Game::handleEvents() {
	//SDL events
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update() {
	//handles the collider updates on all Gameobjects with colliders
	collission->update();
	//updates all GameObjects
	for (unsigned int i = 0; i < allGameObjects.size(); i++) {
			allGameObjects[i]->Update();
	}
	if (GameStarted) {
		enemyManager->Update();
		score++;
		scoreText = "Score: " + std::to_string(score /60);
		ScoreTxt = new Text("Assets/SuperMario256.ttf", 70, scoreText, { 105, 105, 105, 255 }, renderer);
	}
	//Handles main key-input
	switch (event.type) {
		case SDL_KEYDOWN:
			input.setKeyDown(event.key.keysym.scancode);
			//std::cout << event.key.keysym.scancode << std::endl;
			break;
		case SDL_KEYUP:
			input.setKeyUp(event.key.keysym.scancode);
			break;
		}
		//Handles starting the game by pressing space
		if (input.GetKeyDown(44)) {
			if (!GameStarted) {
				//enemyManager->ReGroupAllEnemysNewRound();
				if (player->alive) {
					GameStarted = true;
					GameCheck = true;
			}
		}
	}
	//Handles quiting the game
	if (input.GetKeyDown(41)) {
		event.type = SDL_QUIT;
	}

	if (GameCheck) {
		if (!GameStarted) {
			ControlsText = new Text("Assets/SuperMario256.ttf", 55, "Game over!", { 105, 105, 105, 255 }, renderer);
			goalGameText = "You got pushed off!";
			GoalText = new Text("Assets/SuperMario256.ttf", 50, goalGameText, { 144, 144, 144, 144 }, renderer);
			startGameText = "Restart the game to retry!";
			StartGameTxt = new Text("Assets/SuperMario256.ttf", 60, startGameText, { 105, 105, 105, 255 }, renderer);
			GameCheck = false;
		}
	}
}

void Game::render() {
	//clears last frame
	SDL_RenderClear(renderer);
	//renders map
	map->DrawMap(renderer);
	//renders all GameObjects in the vector allGameObjects
	for (unsigned int i = 0; i < allGameObjects.size(); i++) {
		allGameObjects[i]->Render();
	}
	//Handles renderering text
	if (ScoreTxt != NULL) {
		ScoreTxt->displayText(0, 0, renderer);
	}
	if (!GameStarted) {
		TitleTxt->displayText(500, 650, renderer);
		GoalText->displayText(500, 750, renderer);
		ControlsText->displayText(700, 800, renderer);
		textTimer++;
		if (textTimer > 40) {
			if (!OnOffText) {
				OnOffText = true;
			}
			else {
				OnOffText = false;
			}
			textTimer = 0;
		}
		if (OnOffText) {
			StartGameTxt->displayText(580, 900, renderer);
		}
	}
	//updates the screen with rendering performed
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	//SDL_Quit();
	std::cout << "Game Cleared" << std::endl;
}


