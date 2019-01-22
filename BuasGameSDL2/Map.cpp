#include "Map.h"

Map::Map(SDL_Renderer* ren) {
	scale = 2;

	//Main Tiles
	Tiles.push_back(TextureManager::LoadTexture("Assets/MainTiles/Water.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/MainTiles/Ice.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/MainTiles/Snow.png", ren));

	//Water Tiles
	Tiles.push_back(TextureManager::LoadTexture("Assets/IceToWater/IceWaterLCU.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/IceToWater/IceWaterLCD.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/IceToWater/IceWaterRCU.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/IceToWater/IceWaterRCD.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/IceToWater/IceWaterLML.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/IceToWater/IceWaterRMR.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/IceToWater/IceWaterMMU.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/IceToWater/IceWaterMMD.png", ren));

	//Ice Tiles
	Tiles.push_back(TextureManager::LoadTexture("Assets/SnowToIce/SnowToIceLCU.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/SnowToIce/SnowToIceLCD.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/SnowToIce/SnowToIceRCU.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/SnowToIce/SnowToIceRCD.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/SnowToIce/SnowToIceLMM.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/SnowToIce/SnowToIceRMM.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/SnowToIce/SnowToIceMMU.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/SnowToIce/SnowToIceMMD.png", ren));

	//Snow Tiles
	Tiles.push_back(TextureManager::LoadTexture("Assets/IceToSnow/IceToSnowLCU.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/IceToSnow/IceToSnowLCD.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/IceToSnow/IceToSnowRCU.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/IceToSnow/IceToSnowRCD.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/IceToSnow/IceToSnowLMM.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/IceToSnow/IceToSnowRMM.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/IceToSnow/IceToSnowMMU.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/IceToSnow/IceToSnowMMD.png", ren));

	//Extra Tiles
	Tiles.push_back(TextureManager::LoadTexture("Assets/IceToSnow/IceToSnowUpCorner.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/IceToSnow/DownDownCorner.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/IceToWater/IceWaterCornerUp.png", ren));
	Tiles.push_back(TextureManager::LoadTexture("Assets/IceToWater/IceWaterCornerDown.png", ren));


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

Map::~Map() {

}

void Map::ParseMap(const std::string & name) {
	std::ifstream mapFile(name);
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

void Map::DrawMap(SDL_Renderer* ren) {
	int type = 0;

	for (int row = 0; row < w; row++) {

		for (int column = 0; column < h; column++) {
			type = maps[row][column];
			dest.x = column * 24 * scale;
			dest.y = row * 24 * scale;
			dest.y -= 100;
			TextureManager::Draw(Tiles[type], src, dest, ren);
		}
	}
}

