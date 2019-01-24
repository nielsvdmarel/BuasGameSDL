#include "Game.h"

Game::Game() {

}
Game::~Game() {
	for (unsigned int i = 0; i < allGameObjects.size(); i++) {
		delete allGameObjects[i];
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	// this function is called when destructed
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
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
	map = new Map(renderer);
	map->ParseMap("Assets/Map.txt");
	mapColliders = new MapColliders(renderer, allGameObjects);
	mapColliders->ParseMap("Assets/CollisionMap.txt");
	mapColliders->CreateMapColliders();
	enemyManager = new EnemyManager(renderer, allGameObjects);
	allGameObjects.push_back(new Player(GameObject("Assets/penguins.png", renderer, 1000, 500), input));
	//allGameObjects.push_back(new Enemy(GameObject("Assets/penguinsBad.png", renderer, 1000, 500)));
	collission = new Collision(allGameObjects);
	text = new Text("Assets/SuperMario256.ttf", 30, "Pushy Penguins", {255, 0, 0, 255 }, renderer);
}

void Game::handleEvents() {
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update() {
	text->displayText(500, 500, renderer);
	for (unsigned int i = 0; i < allGameObjects.size(); i++) {
			allGameObjects[i]->Update();
		}
		switch (event.type)
		{
		case SDL_KEYDOWN:
			input.setKeyDown(event.key.keysym.scancode);
			//std::cout << event.key.keysym.scancode << std::endl;
			break;
		case SDL_KEYUP:
			input.setKeyUp(event.key.keysym.scancode);
			break;
		}
		enemyManager->Update();
		collission->update();
}

void Game::render() {
	SDL_RenderClear(renderer);
	map->DrawMap(renderer);
	for (unsigned int i = 0; i < allGameObjects.size(); i++) {
		allGameObjects[i]->Render();
	}
	//add things to render
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	//std::cout << "Game Cleared" << std::endl;
}


