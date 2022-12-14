#pragma once
#include <SDL_image.h>
#include <stdio.h>
#include <sstream>

extern SDL_Renderer* gRenderer;

extern double STARTING_VELOCITY;
extern double GRAVITY;

const int CIRCLES_COUNT = 10;

const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 800;

const int LEVELS = 1;

//bool SEPARATE = false;
//bool BOUNCE = false;

int randInt(int start, int end);

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
};

struct Vector {
	double x, y;

	Vector() {
		x = 0, y = 0;
	}

	Vector(double x, double y) {
		this->x = x;
		this->y = y;
	}

	std::string str() {
		std::stringstream ss;
		ss << "[" << x << ", " << y << "]";
		return ss.str();
	}

	bool operator==(Vector a) {
		if (a.x == x && a.y == y) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator!=(Vector a) {
		return !(Vector(x, y) == a);
	}

	

	Vector operator+(Vector b) {
		return { x + b.x, y + b.y };
	}

	Vector operator-(Vector b) {
		return { x - b.x, y - b.y };
	}

	void operator+=(Vector b) {
		x += b.x;
		y += b.y;
	}

	void operator-=(Vector b) {
		x -= b.x;
		y -= b.y;
	}

	Vector operator*(double a) {
		return { x * a, y * a};
	}

	void operator*=(double a) {
		x *= a;
		y *= a;
	}

	Vector operator/(double b) {
		if (b == 0) {
			printf("DZIELENIE PRZEZ 0!! \n");
			return { 0, 0 };
		}
		return { x/b, y/b};
	}

};

namespace gl {
	Vector vector(Vector position1, Vector position2);
	Vector scale(Vector vec, double scale);
	Vector normalise(Vector vec);
	double length(Vector vec);
	double clamp(double x, double min, double max);
	double angle(Vector p1, Vector p2);
}



const SDL_Color BACKGROUND_COLOR = { 0x0A, 0xC0, 0xFF, 0xFF };

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

	TEXTURES_GROUND,
	TEXTURES_TREE,
	TEXTURES_TREE_TOP,
	TEXTURES_LEFT_SLOPE,
	TEXTURES_MIDDLE,
	TEXTURES_RIGHT_SLOPE,
	TEXTURES_CLOUD,

	TEXTURES_SIZE
};