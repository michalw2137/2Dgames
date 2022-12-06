#pragma once
#include <SDL_image.h>

extern SDL_Renderer* gRenderer;

const int CIRCLES_COUNT = 10;

const int WINDOW_HEIGHT = 500;
const int WINDOW_WIDTH = 500;

const int LEVEL_HEIGHT = 2400;
const int LEVEL_WIDTH = 2400;

const int LEVELS = 3;

//bool SEPARATE = false;
//bool BOUNCE = false;


struct Vector {
	double x, y;

	bool operator==(Vector a) {
		if (a.x == x && a.y == y) {
			return true;
		}
		else {
			return false;
		}
	}
};

namespace gl {
	Vector vector(Vector position1, Vector position2);
	Vector scale(Vector vec, double scale);
	Vector normalise(Vector vec);
	double length(Vector vec);
	double clamp(double x, double min, double max);
}



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