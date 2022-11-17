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
#include "button.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

Camera camera;

Sprite sonic;
Sprite eggman;

Button separateButton;
Button bounceButton;

Circle circles[CIRCLES_COUNT];

//Texture circleSprite;

Level level;

bool initSDL();
void clean();
bool loadTextures();
SDL_Texture* loadTexture(std::string path);

bool SEPARATE = false;
bool BOUNCE = false;

int randInt(int start, int end) {
	return rand() % end + start;
}

void resolveCollisions(int id) {
	for(int i=id; i<CIRCLES_COUNT; i++){

		if (i == id) { // if there are no bugs in here....
			continue;
		}

		double distance = circles[i].distance(&circles[id]);

		if (distance <= circles[i].getRadius() + circles[id].getRadius()) {
			//printf("collision between %d and %d \n", i, id);

			if (SEPARATE) 
			{
				circles[i].separate(&circles[id]);
			}

			if (BOUNCE) 
			{
				circles[i].resolveCollision(&circles[id]);
			}
		}
	}
}

int main(int argc, char* args[]) {
	printf("hello world! \n");
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

	separateButton.changeSize(100, 50);
	bounceButton.changeSize(100, 50);

	separateButton.setPosition(50, WINDOW_WIDTH - 25);
	bounceButton.setPosition(50, WINDOW_WIDTH - 75);

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

	int margin = 50;
	int maxSpeed = 5;
	for (int i = 0; i < CIRCLES_COUNT; i++) {
		circles[i].setRadius(20);
		circles[i].setPosition(randInt(margin, WINDOW_WIDTH- margin), randInt(margin, WINDOW_HEIGHT - margin));
		circles[i].setVelocity(randInt(-maxSpeed, maxSpeed), randInt(-maxSpeed, maxSpeed));
		circles[i].getTexture()->setAlpha(100 + i * 29);
	}

	printf("ball size = %F, %F \n", circles[0].getSize().x, circles[0].getSize().y);
	printf("ball texture size = %F, %F \n", circles[0].getTexture()->getSize().x, circles[0].getTexture()->getSize().y);
	printf("ball radius = %F \n", circles[0].getRadius());


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

				bounceButton.mouseClicked(mouseX, mouseY, &BOUNCE);
				separateButton.mouseClicked(mouseX, mouseY, &SEPARATE);

				printf("BOUNCE = %d\n", BOUNCE);
				printf("SEPARATE = %d\n", SEPARATE);
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

			resolveCollisions(i);

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

		separateButton.render(&camera);
		bounceButton.render(&camera);

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
	if (!separateButton.loadTextures("textures/button1_on.png", "textures/button1_off.png")) {
		printf("Failed to load separate button!\n");
		return false;
	}

	if (!bounceButton.loadTextures("textures/button2_on.png", "textures/button2_off.png")) {
		printf("Failed to load bounce button!\n");
		return false;
	}

	if (!sonic.loadTexture("textures/texture1.png")) {
		printf("Failed to load texture1.png!\n");
		return false;
	}

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

