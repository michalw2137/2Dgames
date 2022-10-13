//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "texture.h"
#include "globals.h"

const SDL_Color BACKGROUND_COLOR = { 0x00, 0xAA, 0xFF, 0xFF };


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

enum codes {
	FAIL = -1,
	SUCCESS = 0
};

Texture squareSprite;
Texture circleSprite;
SDL_Texture* test = NULL;

bool initSDL();
void clean();
bool loadTextures();
SDL_Texture* loadTexture(std::string path);



int main(int argc, char* args[]) {
	printf("hello world! \n");

	if (!initSDL()) {
		printf("Failed to load SDL! \n");
		std::getchar();
		return FAIL;
	}

	if (!loadTextures()) {
		printf("Failed to load textures! \n");
		std::getchar();
		return FAIL;
	}
	printf("loaded succesfully! \n");

	circleSprite.setAlpha(255/2);

	squareSprite.setPosition(WIDTH / 2., HEIGHT / 2.);
	circleSprite.setPosition(WIDTH / 2., HEIGHT / 2.);


	int mouseX = 0, mouseY = 0;
	bool mousePressed = false;

	squareSprite.setAcceleration(0.5);
	double speed = 10;

	SDL_Event e;
	while (true) {
		while (SDL_PollEvent(&e) != 0) {
			if (mousePressed) {
				SDL_GetMouseState(&mouseX, &mouseY);
			}

			switch (e.type) {
			case SDL_QUIT:
				return SUCCESS;

			case SDL_MOUSEBUTTONDOWN:
				mousePressed = true;
				printf("MOUSE PRESSED \n");
				break;

			case SDL_MOUSEBUTTONUP:
				mousePressed = false;
				printf("MOUSE LET GO \n");
				break;

			case SDL_KEYDOWN:
				squareSprite.buttonDown(&e, speed);
				break;

			case SDL_KEYUP:
				squareSprite.buttonUp(&e);
			}	
		}
		
		circleSprite.setTarget(mouseX, mouseY);

		SDL_RenderClear(gRenderer);

		if (abs(squareSprite.getXVelocity()) > 0.001 && abs(squareSprite.getXVelocity()) + 0.001 < speed) {
			printf("changing X speed = %F \n", squareSprite.getXVelocity());
		}
		squareSprite.accelerate();
		squareSprite.move();
		

		circleSprite.accelerateTowardsTarget();
		circleSprite.move();
		

		squareSprite.render();
		circleSprite.render();

		SDL_RenderPresent(gRenderer);

	}

	clean();
	return SUCCESS;
}

bool initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow("zadanie 1", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == NULL) {
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(gRenderer, BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, BACKGROUND_COLOR.a);

	return true;
}

void clean() {
	squareSprite.free();
	circleSprite.free();

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	IMG_Quit();
	printf("IMG quit \n");
	SDL_Quit();
	printf("SDL quit \n");
}


bool loadTextures() {
	if (!squareSprite.loadFromFile("textures/texture1.png")) {
		printf("Failed to load texture1.png!\n");
		return false;
	}

	if (!circleSprite.loadFromFile("textures/texture2.png")) {
		printf("Failed to load texture2.png!\n");
		return false;
	}

	return true;
}

SDL_Texture* loadTexture(std::string path) {
	SDL_Texture* tempTexture = NULL;
	SDL_Surface* tempSurface = IMG_Load(path.c_str());

	if (tempSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		return NULL;
	}

	tempTexture = SDL_CreateTextureFromSurface(gRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	if (tempTexture == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		return NULL;
	}

	return tempTexture;
}

