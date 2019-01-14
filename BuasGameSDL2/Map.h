#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "SDL.h"
#include "TextureManager.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>


class Map {
	public:
		Map(SDL_Renderer* ren);
		~Map();
		void DrawMap(SDL_Renderer* ren);
		void ParseMap(const std::string & mapFile);
		int scale;
		
	private:
		int w = 27, h = 45;
		SDL_Rect src, dest;
		std::vector<SDL_Texture*> Tiles;
		std::vector<std::vector<int>> maps;
};
