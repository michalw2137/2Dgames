#pragma once
#include <SDL_image.h>

extern SDL_Renderer* gRenderer;

const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 600;

const int LEVEL_HEIGHT = 2400;
const int LEVEL_WIDTH = 2400;

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

struct Vector {
	double x, y;
};


const SDL_Color BACKGROUND_COLOR = { 0x00, 0x00, 0x00, 0xFF };

enum codes {
	FAIL = -1,
	SUCCESS = 0
};

enum Textures {
	TEXTURES_WATER,
	TEXTURES_AIR,
	TEXTURES_STONE,
	TEXTURES_BRICK,
	TEXTURES_FIRE,
	TEXTURES_SIZE
};