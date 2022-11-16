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
#include "circle.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

Camera camera;

Sprite sonic;
Sprite eggman;

Circle circles[CIRCLES_COUNT];

//Texture circleSprite;

Level level;

bool initSDL();
void clean();
bool loadTextures();
SDL_Texture* loadTexture(std::string path);


int findCollidingBall(int id) {
	for(int i=0; i<CIRCLES_COUNT; i++){

		if (i == id) { // if there are no bugs in here....
			continue;
		}

		double distance = circles[i].distance(&circles[id]);

		if (distance <= circles[i].getRadius() + circles[id].getRadius()) {
			printf("distance between %d and %d = %F \n", id, i, distance);

			return i;
		}
	}
	return -1;
}

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
	camera.setScale(1);
	camera.setTargetScale(1);


	sonic.setPosition( WINDOW_WIDTH / 2., WINDOW_HEIGHT / 2. );
	sonic.size(100, 100);
	sonic.getTexture()->setSize(100, 100);
	sonic.setAcceleration(0.1);

	eggman.setPosition(WINDOW_WIDTH, WINDOW_HEIGHT);
	eggman.size(100, 100);
	eggman.getTexture()->setSize(100, 100);
	eggman.setAcceleration(0.1);

	//circleSprite.setPosition( WINDOW_WIDTH / 2., WINDOW_HEIGHT / 2. );
	//circleSprite.setTargetPosition( WINDOW_WIDTH / 2. - circleSprite.getSize().x, WINDOW_HEIGHT / 2. - circleSprite.getSize().y );
	double speed = 10;


	int mouseX = 0, mouseY = 0;
	bool mousePressed = false;

	for (int i = 0; i < CIRCLES_COUNT; i++) {
		circles[i].setRadius(20);
		circles[i].setPosition(i * 50, i * 50);
		circles[i].setVelocity(i+1, -i-1);
		circles[i].getTexture()->setAlpha(100 + i * 35);
	}

	SDL_Event e;
	while (true) {
		// EVENTS
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
			case SDL_QUIT:
				return SUCCESS;

			case SDL_MOUSEBUTTONDOWN:
				mousePressed = true;
				//printf("MOUSE PRESSED at (%i, %i)\n", mouseX, mouseY);
				break;

			case SDL_MOUSEBUTTONUP:
				mousePressed = false;
				//printf("MOUSE LET GO at (%i, %i)\n", mouseX, mouseY);
				break;

			case SDL_KEYDOWN:
				//sonic.buttonDown(&e, speed);

				break;

			case SDL_KEYUP:
				//sonic.buttonUp(&e);
				break;

			}
		}
		// LOGIC AND MOVEMENT


		if (mousePressed) {
			SDL_GetMouseState(&mouseX, &mouseY);

			/*eggman.setTargetPosition(mouseX / camera.getScale() + camera.getPosition().x / camera.getScale(),
									mouseY / camera.getScale() + camera.getPosition().y / camera.getScale());
			printf("target [%F, %F] \n", mouseX / camera.getScale() + camera.getPosition().x / camera.getScale(),
									mouseY / camera.getScale() + camera.getPosition().y) / camera.getScale();*/
		}

		for (int i = 0; i < CIRCLES_COUNT; i++) {
			circles[i].move(&camera);
			circles[i].bounceIfOnEdge();

			for (int j = 0; j < CIRCLES_COUNT; j++) {
				int collidingId = findCollidingBall(i);

				if (collidingId == -1) {
					break;
				}
				else {
					printf("collision between %d and %d \n\n", i, collidingId);
					circles[i].resolveCollision(&circles[collidingId]);
					//circles[i].move(&camera);
					//circles[i].bounceIfOnEdge();

					circles[collidingId].move(&camera);
				}
			}
		}

		/*sonic.accelerate();
		sonic.move(&camera);

		eggman.accelerateTowardsTarget();
		eggman.move(&camera);


		if (camera.getScale() == 1) {
			if (sonic.distance(&eggman) > WINDOW_WIDTH) {
				camera.setTargetScale(0.5);
				printf("zooooooooooooooming out \n");
			}
			else {
			}
		}
		
		if (camera.getScale() != camera.getTargetScale()) {
			camera.zoom(0.1);
		} 
		if (camera.getScale() == 0.5) {
			camera.setScale(0.5);
		}*/
		


		// CAMERA
		/*camera.setTargetPosition((sonic.getPosition().x + eggman.getPosition().x) / 2.0f - camera.getSize().x,
							(sonic.getPosition().y + eggman.getPosition().y) / 2.0f - camera.getSize().y);
		camera.setVelocity(0, 0);
		camera.accelerateTowardsTarget();
		camera.move();*/



	// RENDERING
		SDL_RenderClear(gRenderer);

		for (int i = 0; i < CIRCLES_COUNT; i++) {
			circles[i].render(&camera);
		}

		/*level.renderLevel(&camera);
		sonic.render(&camera);
		eggman.render(&camera);*/

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
	sonic.free();
	eggman.free();
	//circleSprite.free();

	for (int i = 0; i < CIRCLES_COUNT; i++) {
		circles[i].free();
	}

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

	for (int i = 0; i < CIRCLES_COUNT; i++) {
		if (!circles[i].loadTexture("textures/circle.png")) {
			printf("Failed to load circle.png!\n");
			return false;
		}
	}

	if (!sonic.loadTexture("textures/texture1.png")) {
		printf("Failed to load texture1.png!\n");
		return false;
	}
	if (!eggman.loadTexture("textures/texture2.png")) {
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

