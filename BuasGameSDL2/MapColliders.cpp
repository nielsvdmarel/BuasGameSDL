#include "MapColliders.h"

MapColliders::MapColliders(SDL_Renderer* ren, bool& gameStarted, std::vector<GameObject*>& gameObjects) : objects(gameObjects), started(gameStarted) {
	scale = 2;
	renderer = ren;
	//Creates a default value for w and h in the (collision) map vector
	for (int i = 0; i < w; i++) {
		maps.push_back(std::vector<int>());
		for (int j = 0; j < h; j++)
			maps[i].push_back(0);
	}
	src.x = 0;
	src.y = 0;
	src.w = dest.w = 24 * scale;
	src.h = dest.h = 24 * scale;
	dest.x = dest.y = 0;
}

MapColliders::~MapColliders() {
	SDL_DestroyRenderer(renderer);
}

//Reads and uses a file to fill in the collision map vector with collision map related data
void MapColliders::ParseMap(const std::string & mapColliderFile) {
	std::ifstream mapFile(mapColliderFile);
	//Checks if mapfile can be opened
	if (!mapFile.is_open()) std::cout << "cant open file\n ";
	//Creates string for every line in file
	std::string line;
	int x = 0;
	int y = 0;
	//Gets lines of data from the text file, using strtok
	while (std::getline(mapFile, line)) {
		char * token = strtok(&line[0], ",");
		y = 0;
		while (token != 0) {
			maps[x][y] = atoi(token);
			y++;
			token = strtok(0, ",");
		}
		x++;
		std::cout << "\n";
	}
	mapFile.close();
}
//Actually creates the colliders, using the data from the collison map vector
void MapColliders::CreateMapColliders() {
	int type = 0;

	for (int row = 0; row < w; row++) {

		for (int column = 0; column < h; column++) {
			type = maps[row][column];
			dest.x = column * 24 * scale;
			dest.y = row * 24 * scale;
			dest.y -= 100;
			if (type != 0) {
				//Use the first line to see the colliders for debug testing, second line makes the colliders without texture

				//GameObject* collider = new GameObject("Assets/Collider.png", renderer, dest.x, dest.y);
				GameObject* collider = new GameObject(0, renderer, dest.x, dest.y, started);
				objects.push_back(collider);
				if (type == 1) {
					collider->tag = "Wall";
				}
				else if (type == 2) {
					collider->tag = "Border";
				}
			}
		}
	}
}

