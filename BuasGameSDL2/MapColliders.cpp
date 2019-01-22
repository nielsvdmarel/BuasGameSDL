#include "MapColliders.h"

MapColliders::MapColliders(SDL_Renderer* ren, std::vector<GameObject*>& gameObjects) : objects(gameObjects)
{
	scale = 2;
	renderer = ren;
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

MapColliders::~MapColliders()
{

}


void MapColliders::ParseMap(const std::string & mapColliderFile)
{
	std::ifstream mapFile(mapColliderFile);
	if (!mapFile.is_open()) std::cout << "cant open file\n ";

	std::string line;
	int x = 0;
	int y = 0;

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

void MapColliders::CreateMapColliders()
{
	int type = 0;

	for (int row = 0; row < w; row++) {

		for (int column = 0; column < h; column++) {
			type = maps[row][column];
			dest.x = column * 24 * scale;
			dest.y = row * 24 * scale;
			dest.y -= 100;
			if (type != 0) {
				GameObject* collider = new GameObject("Assets/Collider.png", renderer, dest.x, dest.y);
				objects.push_back(collider);
				//collider->scale = 40;
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

