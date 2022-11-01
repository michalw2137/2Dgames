#include <SDL_image.h>
#include <iostream>
#include "texture.h"
#include "globals.h"

Texture::Texture() {
	this->pTexture = NULL;

	this->pRenderRect = { 0, 0, 0, 0 };
	this->pSize = { 0, 0 };
	this->pPosition = { 0, 0 };

}

Texture::~Texture() {
	free();
}

void Texture::free() {
	if (this == NULL) {
		printf("null pointer \n");
		return;
	}
	if (pTexture == NULL) {
		return;
	}
	SDL_DestroyTexture(pTexture);
	this->pTexture = NULL;
	this->pSize = {0, 0};
}

bool Texture::loadFromFile(std::string path) {
	free();

	SDL_Surface* tempSurface = IMG_Load(path.c_str());
	if (tempSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		return false;
	}

	SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0xFF, 0xFF, 0xFF));

	this->pTexture = SDL_CreateTextureFromSurface(gRenderer, tempSurface);
	if (this->pTexture == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		return false;
	}

	this->pSize.x = tempSurface->w;
	this->pSize.y = tempSurface->h;

	this->pRenderRect.w = tempSurface->w;
	this->pRenderRect.h = tempSurface->h;

	//printf("loaded texture size [%i, %i] \n", this->pRenderRect.w, this->pRenderRect.h);
	SDL_FreeSurface(tempSurface);
	return true;
}

void Texture::render(double x, double y, Camera* camera) {
	SDL_Rect tempRenderRect = { x - camera->getPosition().x, 
								y - camera->getPosition().y,
								this->pSize.x, 
								this->pSize.y};
	//printf("rendering at (%i, %i) texture size [%i, %i] \n", this->pRenderRect.x, this->pRenderRect.y, this->pRenderRect.w, this->pRenderRect.h);

	SDL_RenderCopy(gRenderer, this->pTexture, NULL, &tempRenderRect);
}

void Texture::setAlpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(pTexture, alpha);
}

Vector Texture::getSize() {
	return this->pSize;
}

void Texture::setPosition(double x, double y) {
	this->pPosition = { x, y };
}

void Texture::setSize(double x, double y) {
	this->pSize.x = x;
	this->pSize.y = y;
}

Vector Texture::getPosition() {
	return this->pPosition;
}

SDL_Texture* Texture::getTexture() {
	return pTexture;
}



