//Using SDL, SDL_image, standard IO, and strings

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "texture.h"
#include "globals.h"
#include "level.h"
#include "sprite.h"
#include "camera.h"
#include "ball.h"
#include "box.h"
#include "target.h"
#include "button.h"
#include "screen.h"
#include <windows.h>
#include <iostream>
#include "App.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

bool initSDL(const char* windowName);
void clean();
SDL_Texture* loadTexture(std::string path);


int main(int argc, char* args[]) {
	srand(time(NULL));

	if (!initSDL("test App")) {
		printf("Failed to load SDL! \n");
		std::getchar();
		return FAIL;
	}


	printf("loaded succesfully! \n");

	try {
		App::setup();
	}
	catch (const char* message) {
		std::cout << "Failed to setup App, message: " << message << "\n";
	}
	

	while (true) {
		try {
			App::loop();
		}
		catch (const char* message) {
			std::cout << "Loop stopped, message: " << message << "\n";
			break;
		}	
	}
	clean();
	return SUCCESS;
}

bool initSDL(const char * windowName) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow(windowName, 10, 30, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	IMG_Quit();
	printf("IMG quit \n");
	SDL_Quit();
	printf("SDL quit \n");
}
