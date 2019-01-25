#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
#include <string>
#include <iostream>

class Text
{
public:
	Text(const std::string &fontPath,int fontSize,const std::string &messageText,const SDL_Color &color, SDL_Renderer* ren);
	~Text();
	void displayText(int x, int y, SDL_Renderer* ren);
	SDL_Texture *loadFont(const std::string &fontPath, int fontSize, const std::string &messageText,const SDL_Color &color);
	SDL_Renderer* renderer;
	SDL_Texture * _textTexture;
	SDL_Rect textRect;
private:
};
