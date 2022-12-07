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

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

Camera camera;

Box box;
Ball ball;

Target target;

Level level;
Level levels[LEVELS];

Screen screen;

int currentLevel = -1;

int pointsBall = 0, pointsBox = 0;

bool initSDL();
void clean();
bool loadTextures();
SDL_Texture* loadTexture(std::string path);


int randInt(int start, int end) {
	return rand() % end + start;
}

//void resolveCollisions(int id) {
//	for(int i=id; i<CIRCLES_COUNT; i++){
//
//		if (i == id) { // if there are no bugs in here....
//			continue;
//		}
//
//		double distance = circles[i].distance(&circles[id]);
//
//		if (distance <= circles[i].getRadius() + circles[id].getRadius()) {
//			//printf("collision between %d and %d \n", i, id);
//
//			
//			circles[i].separate(&circles[id]);
//			
//
//			
//			circles[i].resolveCollision(&circles[id]);
//			
//		}
//	}
//}

void setRandomPosition(Sprite* sprite) {
	double x = 0, y = 0;
	do {
		x = 50 * randInt(0, level.getWidth());
		y = 50 * randInt(0, level.getHeight());
	} while (level.touchesWall({ x, y }));
	sprite->setPosition(x, y);
}

void resetLevel() {
	currentLevel++;

	if (currentLevel >= LEVELS) {
		currentLevel = 0;
		printf("POINTS: \n circle: %d \n square: %d \n", pointsBall, pointsBox);
		pointsBall = 0;
		pointsBox = 0;
	}

	level = levels[currentLevel];
	setRandomPosition(&box);
	setRandomPosition(&ball);
	do {
		setRandomPosition(&target);
	} while (target.getPosition() == ball.getPosition() || target.getPosition() == box.getPosition());
	
	//printf("\n loaded level %d \n", currentLevel);
}

int main(int argc, char* args[]) {
	srand(time(NULL));

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

	camera.setScale(1);
	camera.setTargetScale(1);

	box.size(50, 50);
	box.setAcceleration(0.1);

	ball.setAcceleration(0.1);
	ball.setRadius(25);
	
	target.size(30, 30);
	target.getTexture()->setSize(50, 50);

	double speed = 10;

	int mouseX = 0, mouseY = 0;
	bool mousePressed = false;


	resetLevel();

	SDL_Event e;
	while (true) {
		// EVENTS
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
			case SDL_QUIT:
				return SUCCESS;

			case SDL_MOUSEBUTTONDOWN:
				mousePressed = true;
				SDL_GetMouseState(&mouseX, &mouseY);
				break;

			case SDL_MOUSEBUTTONUP:
				mousePressed = false;
				break;

			case SDL_KEYDOWN:
				box.arrowDown(&e, speed);
				ball.wsadDown(&e, speed);

				break;

			case SDL_KEYUP:
				box.arrowUp(&e);
				ball.wsadUp(&e);

				break;

			}
		}
	// LOGIC AND MOVEMENT		

		box.accelerate();
		box.move(&camera);

		ball.accelerate();
		ball.move(&camera);


		if (camera.getScale() == 1) {
			if (box.distance(&ball) > WINDOW_WIDTH) {
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
		}
		
		level.resolveWallCollisions(&box);
		level.resolveWallCollisions(&ball);

		if (target.checkForCollision(&box)) {
			//level = levels[target.getCurrentLevel()];
			printf("point for box \n");
			pointsBox++;

			currentLevel + 1 < LEVELS ? screen.boxWins() : screen.gameOver();

			resetLevel();
		} else if (target.checkForCollision(&ball)) {
			//level = levels[target.getCurrentLevel()];
			printf("point for ball \n");
			pointsBall++;

			currentLevel + 1 < LEVELS ? screen.ballWins() : screen.gameOver();

			resetLevel();
		}
		else {
			screen.emptyScreen();
		}
		

	// CAMERA
	camera.setTargetPosition((box.getPosition().x + ball.getPosition().x) / 2.0f - camera.getSize().x,
						(box.getPosition().y + ball.getPosition().y) / 2.0f - camera.getSize().y);
	camera.setVelocity(0, 0);
	camera.accelerateTowardsTarget();
	camera.move();

	// RENDERING
		SDL_RenderClear(gRenderer);

		level.renderLevel(&camera);

		box.render(&camera);
		ball.render(&camera);

		target.render(&camera);

		//printf("a\n");
		screen.render();
		//printf("c\n");
		SDL_RenderPresent(gRenderer);

		Sleep(screen.getWait());
	}

	clean();
	return SUCCESS;
}

bool initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow("zadanie 7_8", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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
	box.free();
	ball.free();
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
	if (!screen.loadTextures()) {
		printf("Failed to load screens!\n");
		return false;
	}
	if (!box.loadTexture("textures/texture1.png")) {
		printf("Failed to load texture1.png!\n");
		return false;
	}
	if (!ball.loadTexture("textures/texture2.png")) {
		printf("Failed to load texture2.png!\n");
		return false;
	}
	if (!target.loadTexture("textures/target.png")) {
		printf("Failed to load target.png!\n");
		return false;
	}

	if (!levels[0].loadLevelFromFile("levels/level1.txt", 16, 16)) {
		printf("Failed to load level.txt!\n");
		return false;
	}
	if (!levels[0].loadTextures()) {
		printf("Failed to load some of the textures!\n");
		return false;
	}

	if (!levels[1].loadLevelFromFile("levels/level2.txt", 20, 20)) {
		printf("Failed to load level.txt!\n");
		return false;
	}
	if (!levels[1].loadTextures()) {
		printf("Failed to load some of the textures!\n");
		return false;
	}

	if (!levels[2].loadLevelFromFile("levels/level3.txt", 24, 24)) {
		printf("Failed to load level.txt!\n");
		return false;
	}
	if (!levels[2].loadTextures()) {
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

