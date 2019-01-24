#include "Text.h"

Text::Text(const std::string & fontPath, int fontSize, const std::string & messageText,const SDL_Color & color, SDL_Renderer* ren)
{
	renderer = ren;
	textTexture = loadFont(fontPath, fontSize, messageText, color);
	SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
}

Text::~Text()
{

}

void Text::displayText(int x, int y, SDL_Renderer* ren)
{
	textRect.x = x;
	textRect.y = y;
	SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
}

SDL_Texture * Text::loadFont(const std::string & fontPath, int fontSize, const std::string & messageText, const SDL_Color & color)
{
	TTF_Font *font = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (!font) {
		std::cout << "failed to load font" << std::endl;
	}
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, messageText.c_str(), color);
	if (!textSurface) {
		std::cout << "Failed to create text surface";
	}
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (!textTexture) {
		std::cout << "Failed to create text texture";
	}
	SDL_FreeSurface(textSurface);
		return textTexture;
	
}


