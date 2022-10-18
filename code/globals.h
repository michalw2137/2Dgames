#pragma once
#include <SDL_image.h>

extern SDL_Renderer* gRenderer;

const int HEIGHT = 600;
const int WIDTH = 800;

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

struct Vector {
	double x, y;
};