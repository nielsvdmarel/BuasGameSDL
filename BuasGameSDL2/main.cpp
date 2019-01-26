#include "Game.h"
#include "windows.h"

int main(int argc, char* argv[])
{
	char result[256];
	int bytes = GetModuleFileName(NULL, result, 256);
	std::cout << result << "\n";

	//Limits frames per second to max 60
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	//Creates new Game object
	Game* game = new Game();
	//Starts the Game init
	game->init("Pushy-Penguins", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, false);
	while (game->running())
	{
		//Update
		frameStart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	game->clean();
	delete game;
	return 0;
}