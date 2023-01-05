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

const int LEVEL_HEIGHT = 2400;
const int LEVEL_WIDTH = 2400;

const int LEVELS = 1;

//bool SEPARATE = false;
//bool BOUNCE = false;

int randInt(int start, int end);

struct Vector {
	double x, y;

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