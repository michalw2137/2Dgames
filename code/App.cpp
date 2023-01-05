#pragma once

#include "App.h"
#include <windows.h>
#include <iostream>

static Camera camera;

static Box box;
static Ball ball;

static Target target;

static Sprite mountains;
static Sprite forest;
static Sprite clouds;


static Level level;
static Level levels[LEVELS];

static Screen screen;

static Texture arrow;

static int currentLevel = -1;

static int pointsBall = 0, pointsBox = 0;

static int mouseX = 0, mouseY = 0;
static bool mousePressed = false;
static SDL_Event e;

static double speed = 0.3;

double jumpHeight = 100; 
double jumpDistance = 100; 

double STARTING_VELOCITY = 2 * jumpHeight * speed / jumpDistance;
double GRAVITY = 2 * jumpHeight * speed * speed / jumpDistance / jumpDistance;

static Clock timer;

void recalculateV0_G() {
	STARTING_VELOCITY = 2 * jumpHeight * speed / jumpDistance;
	GRAVITY = 2 * jumpHeight * speed * speed / jumpDistance / jumpDistance;

	box.setAcceleration(0, GRAVITY);
	ball.setAcceleration(0, GRAVITY);

	printf("jumpHeight = %F\n", jumpHeight);
	printf("jumpDistance = %F\n", jumpDistance);
	printf("G = %F\n", GRAVITY);
	printf("V0 = %F\n\n", STARTING_VELOCITY);

}

void App::setup() {
	try {
		box.loadTexture("textures/texture1.png");
		ball.loadTexture("textures/texture2.png");
		target.loadTexture("textures/target.png");

		levels[0].loadLevel("levels/level.txt", 52, 11);
		mountains.loadTexture("textures/mountains.png");
		clouds.loadTexture("textures/clouds.png");
		forest.loadTexture("textures/forest.png");
	}
	catch (std::string message) {
		printf("%s", message.c_str());
		throw("Failed to load textures");
	}

	std::cout << "\ngravity = " << GRAVITY;

	std::cout << "\nv0= " << STARTING_VELOCITY << "\n";

	camera.setScale(1);
	camera.setTargetScale(1);

	box.size(50, 50);

	box.setAcceleration(0, GRAVITY);
	ball.setAcceleration(0, GRAVITY);

	box.setVelocity(0, 0);
	ball.setVelocity(0, 0);

	ball.setRadius(25);

	target.size(30, 30);
	target.getTexture()->setSize(50, 50);

	resetLevel();
	
}

void App::loop() {
	double deltaTime = timer.tick();
	//std::cout << "\ndelta time = " << deltaTime;

	while (SDL_PollEvent(&e) != 0) {
		switch (e.type) {
		case SDL_QUIT:
			throw("app closed");

		case SDL_MOUSEBUTTONDOWN:
			mousePressed = true;
			SDL_GetMouseState(&mouseX, &mouseY);
			break;

		case SDL_MOUSEBUTTONUP:
			mousePressed = false;
			break;

		case SDL_KEYDOWN:
			if (e.key.keysym.sym == SDLK_KP_8) {
				jumpHeight += 10;
				recalculateV0_G();
			}
			
			if (e.key.keysym.sym == SDLK_KP_2) {
				jumpHeight -= 10;
				recalculateV0_G();
			}

			if (e.key.keysym.sym == SDLK_KP_6) {
				jumpDistance += 10;
				recalculateV0_G();
			}

			if (e.key.keysym.sym == SDLK_KP_4) {
				jumpDistance -= 10;
				recalculateV0_G();
			}

			box.arrowDown(&e, speed);
			ball.wsadDown(&e, speed);

			if (e.key.keysym.sym == SDLK_UP && box.canJump())
				box.setBoosted(true);

			if (e.key.keysym.sym == SDLK_w && ball.canJump())
				ball.setBoosted(true);

			break;

		case SDL_KEYUP:
			box.arrowUp(&e);
			ball.wsadUp(&e);

			if (e.key.keysym.sym == SDLK_UP && box.canJump())
				box.jump(STARTING_VELOCITY);

			if (e.key.keysym.sym == SDLK_w && ball.canJump())
				ball.jump(STARTING_VELOCITY);

			break;

		}
	}
	// LOGIC AND MOVEMENT		
	box.boost();
	ball.boost();

	box.accelerate(deltaTime, {0, GRAVITY});
	ball.accelerate(deltaTime, {0, GRAVITY});


	level.resolveWallCollisions(&box);
	level.resolveWallCollisions(&ball);

	if (target.checkForCollision(&box)) {
		printf("point for box \n");
		pointsBox++;

		currentLevel + 1 < LEVELS ? screen.boxWins() : screen.gameOver();

		resetLevel();
	}
	else if (target.checkForCollision(&ball)) {
		printf("point for ball \n");
		pointsBall++;

		currentLevel + 1 < LEVELS ? screen.ballWins() : screen.gameOver();

		resetLevel();
	}
	else {
		screen.emptyScreen();
	}

	// CAMERA
	Vector pos = (box.getPosition() + ball.getPosition()) / 2.0;
	//printf("%F, %F \n", camera.getSize().x / 2., camera.getSize().y / 2.);
	camera.moveTo(pos.x - camera.getSize().x / 2.
		, pos.y - camera.getSize().y * 0.7
	);


// RENDERING
	SDL_RenderClear(gRenderer);

	printf("camera delta = %s \n", camera.getDelta().str().c_str());
	mountains.changeX(camera.getDelta().x * 0.3);
	forest.changeX(camera.getDelta().x * 0.5);
	clouds.changeX(camera.getDelta().x * 0.1);

	mountains.render(&camera);
	forest.render(&camera);
	clouds.render(&camera);


	level.renderLevel(&camera);

	box.render(&camera);
	ball.render(&camera);

	SDL_RenderPresent(gRenderer);

	Sleep(screen.getWait());
}


bool App::loadTextures() {
	if (!arrow.loadFromFile("textures/arrow.png")) {
		printf("Failed to load arrow!\n");
		return false;
	}
	if (!screen.loadTextures()) {
		printf("Failed to load screens!\n");
		return false;
	}
	
	return true;
}

void App::setRandomPosition(Sprite* sprite) {
	double x = 0, y = 0;
	do {
		x = 50 * randInt(0, level.getWidth());
		y = 50 * randInt(0, level.getHeight());
	} while (level.touchesWall({ x, y }));
	sprite->setPosition(x, y);
}

void App::resetLevel() {
	currentLevel++;

	if (currentLevel >= LEVELS) {
		currentLevel = 0;
		printf("\nPOINTS: \n circle: %d \n square: %d \n\n", pointsBall, pointsBox);
		pointsBall = 0;
		pointsBox = 0;
	}

	level = levels[currentLevel];
	//setRandomPosition(&box);
	//setRandomPosition(&ball);
	/*do {
		setRandomPosition(&target);
	} while (target.getPosition() == ball.getPosition() || target.getPosition() == box.getPosition());*/

	box.setPosition(600, 300);
	ball.setPosition(600, 250);
	target.setPosition(3000, 500);

	//CAMERA
	camera.setScale(1);
	camera.moveTo(level.getWidth() * 25 - camera.getSize().x / 2., level.getHeight() * 25 - camera.getSize().y / 2.);

}


