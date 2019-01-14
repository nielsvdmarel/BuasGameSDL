#include "Game.h"

Game::Game() {

}
Game::~Game() {
	for (unsigned int i = 0; i < allGameObjects.size(); i++) {
		delete allGameObjects[i];
	}
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
	enemyManager = new EnemyManager(renderer, allGameObjects);
	allGameObjects.push_back(new Enemy(GameObject("Assets/p22B.png", renderer, 2000, 500)));
	allGameObjects.push_back(new Player( GameObject("Assets/p21.png", renderer, 0 , 0), input));
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
	std::cout << "Game Cleared" << std::endl;
}


