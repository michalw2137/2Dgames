#include <SDL_image.h>
#include <iostream>
#include "texture.h"
#include "globals.h"

Texture::Texture() {
	pTexture = NULL;

	pWidth = 0;
	pHeight = 0;

	pXPosition = 0;
	pYPosition = 0;

	pXVelocity = 0;
	pYVelocity = 0;

	pXTargetVelocity = 0;
	pYTargetVelocity = 0;

	pTargetX = 0;
	pTargetY = 0;

	acceleration = 0;

	pRenderRect = { 0, 0, 0, 0 };
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
	pTexture = NULL;
	pWidth = 0;
	pHeight = 0;
}

bool Texture::loadFromFile(std::string path) {
	free();

	SDL_Surface* tempSurface = IMG_Load(path.c_str());
	if (tempSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		return false;
	}

	SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0xFF, 0xFF, 0xFF));

	pTexture = SDL_CreateTextureFromSurface(gRenderer, tempSurface);
	if (pTexture == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		return false;
	}

	pWidth = tempSurface->w;
	pHeight = tempSurface->h;

	pRenderRect.w = pWidth;
	pRenderRect.h = pHeight;

	SDL_FreeSurface(tempSurface);
	return true;
}

void Texture::render() {
	pRenderRect.x = int(pXPosition);
	pRenderRect.y = int(pYPosition);
	SDL_RenderCopy(gRenderer, pTexture, NULL, &pRenderRect);
	//SDL_Renderer, SDL_Texture, NULL, SDL_Rect
									//{ x, y, width, height}
//std::cout << pRenderRect.x << " " << pRenderRect.y << " " << pRenderRect.w << " " << pRenderRect.h << "\n";
}

void Texture::setPosition(double x, double y) {
	pXPosition = x;
	pYPosition = y;
}

void Texture::setAcceleration(double a) {
	acceleration = a;
}

int Texture::getHeight() {
	return pHeight;
}

void Texture::setXVelocity(double velocity) {
	pXVelocity = velocity;
}

void Texture::setYVelocity(double velocity) {
	pYVelocity = velocity;
}

void Texture::setXTargetVelocity(double velocity) {
	pXTargetVelocity = velocity;
}

void Texture::setYTargetVelocity(double velocity) {
	pYTargetVelocity = velocity;
}

void Texture::move() {
	/*if (pXPosition + pXVelocity <= 0 || pXPosition + pXVelocity + pWidth >= WIDTH) {
		pXVelocity *= -1;
	}
	if (pYPosition + pYVelocity <= 0 || pYPosition + pYVelocity + pHeight >= HEIGHT) {
		pYVelocity *= -1;
	}*/
	pXPosition += pXVelocity;
	pYPosition += pYVelocity;
}

void Texture::accelerate() {
	pXVelocity = pXVelocity * acceleration + pXTargetVelocity * (1 - acceleration);
	pYVelocity = pYVelocity * acceleration + pYTargetVelocity * (1 - acceleration);
}

void Texture::setAlpha(Uint8 alpha) {
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(pTexture, alpha);
}

int Texture::getWidth() {
	return pWidth;
}

int Texture::getXPosition() {
	return pXPosition;
}

int Texture::getYPosition() {
	return pYPosition;
}

double Texture::getXVelocity() {
	return pXVelocity;
}

double Texture::getYVelocity() {
	return pYVelocity;
}

SDL_Texture* Texture::getTexture() {
	return pTexture;
}

void Texture::setTarget(double x, double y) {
	pTargetX = x;
	pTargetY = y;
}

void Texture::accelerateTowardsTarget() {
	pXVelocity = (pTargetX - pXPosition - pWidth/2) / 20;
	pYVelocity = (pTargetY - pYPosition - pHeight / 2) / 20;
}

void Texture::buttonDown(SDL_Event* e, double speed) {
	switch (e->key.keysym.sym) {
		case SDLK_UP:
			if (pYTargetVelocity != -speed)
				printf("UP \n");
			setYTargetVelocity(-speed);

			break;

		case SDLK_DOWN:
			if (pYTargetVelocity != speed)
				printf("DOWN \n");
			setYTargetVelocity(speed);

			break;

		case SDLK_LEFT:
			if (pXTargetVelocity != -speed)
				printf("LEFT \n");
			setXTargetVelocity(-speed);

			break;

		case SDLK_RIGHT:
			if (pXTargetVelocity != speed)
				printf("RIGHT \n");
			setXTargetVelocity(speed);

			break;

		default:
			break;
	}
}

void Texture::buttonUp(SDL_Event* e) {
	switch (e->key.keysym.sym) {
	case SDLK_UP:
		printf("UP released \n");
		setYTargetVelocity(0);

		break;

	case SDLK_DOWN:
		printf("DOWN released \n");
		setYTargetVelocity(0);

		break;

	case SDLK_LEFT:
		printf("LEFT released \n");
		setXTargetVelocity(0);

		break;

	case SDLK_RIGHT:
		printf("RIGHT released \n");
		setXTargetVelocity(0);

		break;

	default:
		break;
	}
}

