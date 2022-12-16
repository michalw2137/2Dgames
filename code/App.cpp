#pragma once

#include "App.h"
#include <windows.h>
#include <iostream>

static Camera camera;

static Box box;
static Ball ball;

static Target target;

static Level level;
static Level levels[LEVELS];

static Screen screen;

static Texture arrow;

static int currentLevel = -1;

static int pointsBall = 0, pointsBox = 0;

static double speed = 1;
static int mouseX = 0, mouseY = 0;
static bool mousePressed = false;
static SDL_Event e;

double jumpHeight = 0.01;
double jumpTime = 2;


double GRAVITY = 2 * jumpHeight / jumpTime / jumpTime;
double STARTING_VELOCITY = 200 * jumpHeight / jumpTime;

void App::setup() {
	if (!loadTextures()) {
		printf("Failed to load textures! \n");
		std::getchar();
		throw("Failed to load textures");
	}

	std::cout << "\ngravity = " << GRAVITY;

	std::cout << "\nv0= " << STARTING_VELOCITY << "\n";

	camera.setScale(1);
	camera.setTargetScale(1);

	box.size(50, 50);

	box.setAcceleration(0, GRAVITY);
	ball.setAcceleration(0, GRAVITY);

	ball.setRadius(25);

	target.size(30, 30);
	target.getTexture()->setSize(50, 50);

	resetLevel();

}

struct Clock
{
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;

	double tick()
	{
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

		return deltaTime;
	}
} timer;

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
			if (e.key.keysym.sym == SDLK_UP && e.key.repeat == 0)
				box.jump(STARTING_VELOCITY);

			if (e.key.keysym.sym == SDLK_w && e.key.repeat == 0)
				ball.jump(STARTING_VELOCITY);

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
		//camera.isSeen(&box);

	box.accelerate(deltaTime);
	ball.accelerate(deltaTime);

	//box.move(&camera);

	//ball.accelerate(deltaTime);
	//ball.move(&camera);


	/*if (camera.getScale() == 1) {
		if (box.distance(&ball) > WINDOW_WIDTH) {
			camera.setTargetScale(0.5);
			printf("zooooooooooooooming out \n");
		}
		else {
		}
	}*/

	/*if (camera.getScale() != camera.getTargetScale()) {
		camera.zoom(0.1);
	}
	if (camera.getScale() == 0.5) {
		camera.setScale(0.5);
	}*/

	level.resolveWallCollisions(&box);
	level.resolveWallCollisions(&ball);

	if (target.checkForCollision(&box)) {
		//level = levels[target.getCurrentLevel()];
		printf("point for box \n");
		pointsBox++;

		currentLevel + 1 < LEVELS ? screen.boxWins() : screen.gameOver();

		resetLevel();
	}
	else if (target.checkForCollision(&ball)) {
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
	Vector pos = (box.getPosition() + ball.getPosition()) / 2.0;
	//printf("%F, %F \n", camera.getSize().x / 2., camera.getSize().y / 2.);
	camera.setPosition(pos.x - camera.getSize().x / 2.
		, pos.y - camera.getSize().y / 2.
	);
	//if (!camera.isSeen(&box) ) {
	//	printf("box isnt seen \n");
	//}
	////if (!camera.isSeen(&ball)) {
	////	printf("ball isnt seen \n");
	////}
	//if (!camera.isSeen(&box) && camera.getScale() > 0.3) {
	//	printf("box isnt seen \n");

	//	camera.setScale(camera.getScale() - 0.05);

	//	Vector pos = (box.getPosition() + ball.getPosition()) / 2.0;
	//	camera.setPosition(pos.x, pos.y);

	//}
	//if (!camera.isSeen(&ball) && camera.getScale() > 0.3) {
	//	printf("ball isnt seen \n");

	//	camera.setScale(camera.getScale() - 0.05);

	//	Vector pos = (box.getPosition() + ball.getPosition()) / 2.0;
	//	camera.setPosition(pos.x, pos.y);
	//}

// RENDERING
	SDL_RenderClear(gRenderer);

	level.renderLevel(&camera);

	box.render(&camera);
	ball.render(&camera);

	target.render(&camera);

	if (!camera.isSeen(&target, false)) {
		arrow.setPosition(400, 400);
		arrow.render(gl::angle(target.getPosition(), camera.getPosition()));
	}

	//printf("a\n");
	screen.render();
	//printf("c\n");
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
	setRandomPosition(&box);
	setRandomPosition(&ball);
	do {
		setRandomPosition(&target);
	} while (target.getPosition() == ball.getPosition() || target.getPosition() == box.getPosition());

	//CAMERA
	camera.setScale(1);
	camera.setPosition(level.getWidth() * 25 - camera.getSize().x / 2., level.getHeight() * 25 - camera.getSize().y / 2.);

}

