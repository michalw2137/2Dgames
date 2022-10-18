#include <SDL_image.h>
#include <iostream>
#include "texture.h"
#include "globals.h"

Texture::Texture() {
	this->pTexture = NULL;

	this->acceleration = 0;

	this->pRenderRect = { 0, 0, 0, 0 };
	this->pSize = { 0, 0 };
	this->pPosition = { 0, 0 };
	this->pVelocity = { 0, 0 };
	this->pTargetVelocity = { 0, 0 };
	this->pTargetPosition = { 0,0 };
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

	this->pRenderRect.w = this->pSize.x;
	this->pRenderRect.h = this->pSize.x;

	SDL_FreeSurface(tempSurface);
	return true;
}

void Texture::render() {
	this->pRenderRect.x = int(this->pPosition.x);
	this->pRenderRect.y = int(this->pPosition.y);
	SDL_RenderCopy(gRenderer, this->pTexture, NULL, &this->pRenderRect);
}

void Texture::accelerate() {
	this->pVelocity.x = this->pVelocity.x * acceleration + this->pTargetVelocity.x * (1 - acceleration);
	this->pVelocity.y = this->pVelocity.y * acceleration + this->pTargetVelocity.y * (1 - acceleration);
}

void Texture::accelerateTowardsTarget() {
	this->pVelocity.x = (this->pTargetPosition.x - this->pPosition.x - (this->pSize.x / 2.)) / 20.;
	this->pVelocity.y = (this->pTargetPosition.y - this->pPosition.y - (this->pSize.y / 2.)) / 20.;
}

void Texture::move() {
	this->pPosition.x += this->pVelocity.x;
	this->pPosition.y += this->pVelocity.y;
}

void Texture::buttonDown(SDL_Event* e, double speed) {
	switch (e->key.keysym.sym) {
	case SDLK_UP:
		if (e->key.repeat == 0) {
			printf("UP \n");
		}
		this->pTargetVelocity.y = -speed;
		break;

	case SDLK_DOWN:
		if (e->key.repeat == 0) {
			printf("DOWN \n");
		}
		this->pTargetVelocity.y = speed;
		break;

	case SDLK_LEFT:
		if (e->key.repeat == 0) {
			printf("LEFT \n");
		}
		this->pTargetVelocity.x = -speed;
		break;

	case SDLK_RIGHT:
		if (e->key.repeat == 0) {
			printf("RIGHT \n");
		}
		this->pTargetVelocity.x = speed;
		break;

	default: break;
	}
}

void Texture::buttonUp(SDL_Event* e) {
	switch (e->key.keysym.sym) {
	case SDLK_UP:
		printf("UP released \n");
		this->pTargetVelocity.y = 0;
		break;

	case SDLK_DOWN:
		printf("DOWN released \n");
		this->pTargetVelocity.y = 0;
		break;

	case SDLK_LEFT:
		printf("LEFT released \n");
		this->pTargetVelocity.x = 0;
		break;

	case SDLK_RIGHT:
		printf("RIGHT released \n");
		this->pTargetVelocity.x = 0;
		break;

	default: break;
	}
}

void Texture::setAlpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(pTexture, alpha);
}

void Texture::setTargetPosition(double x, double y) {
	this->pTargetPosition.x = x;
	this->pTargetPosition.y = y;
}

void Texture::setPosition(double x, double y) {
	this->pPosition = { x, y };
}

void Texture::setAcceleration(double a) {
	acceleration = a;
}

Vector Texture::getSize() {
	return this->pSize;
}

Vector Texture::getPosition() {
	return this->pPosition;
}

Vector Texture::getTargetPosition() {
	return this->pTargetPosition;
}

Vector Texture::getVelocity() {
	return this->pVelocity;
}

Vector Texture::getTargetVelocity() {
	return this->pTargetVelocity;
}

SDL_Texture* Texture::getTexture() {
	return pTexture;
}



