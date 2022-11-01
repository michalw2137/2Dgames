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

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

Camera camera;
Sprite squareSprite;
//Texture circleSprite;

Level level;

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


	//circleSprite.setAlpha(255/2);

	squareSprite.setPosition( WINDOW_WIDTH / 2., WINDOW_HEIGHT / 2. );
	squareSprite.setSize(10, 10);
	squareSprite.getTexture()->setSize(10, 10);
	squareSprite.setAcceleration(0.1);

	//circleSprite.setPosition( WINDOW_WIDTH / 2., WINDOW_HEIGHT / 2. );
	//circleSprite.setTargetPosition( WINDOW_WIDTH / 2. - circleSprite.getSize().x, WINDOW_HEIGHT / 2. - circleSprite.getSize().y );
	double speed = 10;


	int mouseX = 0, mouseY = 0;
	bool mousePressed = false;

	SDL_Event e;
	while (true) {
		// EVENTS
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
			case SDL_QUIT:
				return SUCCESS;

			case SDL_MOUSEBUTTONDOWN:
				mousePressed = true;
				printf("MOUSE PRESSED at (%i, %i)\n", mouseX, mouseY);
				break;

			case SDL_MOUSEBUTTONUP:
				mousePressed = false;
				printf("MOUSE LET GO at (%i, %i)\n", mouseX, mouseY);
				break;

			case SDL_KEYDOWN:
				squareSprite.buttonDown(&e, speed);

				break;

			case SDL_KEYUP:
				squareSprite.buttonUp(&e);


			}
		}
		// LOGIC AND MOVEMENT


		if (mousePressed) {
			SDL_GetMouseState(&mouseX, &mouseY);
			//circleSprite.setTargetPosition(mouseX, mouseY);
		}

		squareSprite.accelerate();
		squareSprite.move();


		camera.positionInMiddle(squareSprite.getPosition().x + 10 * squareSprite.getVelocity().x, 
								squareSprite.getPosition().y + 10 * squareSprite.getVelocity().y,
								squareSprite.getSize().x, 
								squareSprite.getSize().y);
		camera.keepInBounds();

		


	// RENDERING
		SDL_RenderClear(gRenderer);

		level.renderLevel(&camera);
		squareSprite.render(&camera);
		//circleSprite.render();

		SDL_RenderPresent(gRenderer);


		// CONSOLE OUTPUT
		if (abs(squareSprite.getVelocity().x) > 0.1 && abs(squareSprite.getVelocity().x) + 0.1 < speed) {
			printf("x vel = %F \n", squareSprite.getVelocity().x);
		}

	}

	clean();
	return SUCCESS;
}

bool initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow("zadanie 4", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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
	//circleSprite.free();

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
	if (!squareSprite.loadTexture("textures/texture1.png")) {
		printf("Failed to load texture1.png!\n");
		return false;
	}

	/*if (!circleSprite.loadFromFile("textures/texture2.png")) {
		printf("Failed to load texture2.png!\n");
		return false;
	}*/

	if (!level.laodLevelFromFile("levels/level.txt")) {
		printf("Failed to load level.txt!\n");
		return false;
	}

	if (!level.loadTextures()) {
		printf("Failed to load some of the textures!\n");
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

