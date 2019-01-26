#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "SDL.h"
#include "GameObject.h"

class MapColliders {
public:
	MapColliders(SDL_Renderer* ren, bool& gameStarted, std::vector<GameObject*>& gameObjects);
	~MapColliders();
	void ParseMap(const std::string & mapColliderFile);
	void CreateMapColliders();
	int scale;
private:
	bool& started;
	SDL_Renderer* renderer;
	int w = 27, h = 45;
	SDL_Rect src, dest;
	std::vector<std::vector<int>> maps;
	std::vector<GameObject*>& objects;
};