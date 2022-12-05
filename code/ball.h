#pragma once
#include <SDL.h>
#include <string>
#include "globals.h"
#include "sprite.h"
#include "box.h"

class Ball: public Sprite{

public:

	void resolveCollision(Ball* other);

	void separate(Ball* other);

	void bounceIfOnEdge();

	double getRadius();

	void setRadius(double r);

	std::string str();

	void resolveBoxCollision(Box* other);

private:
	double mass = 1;
	double radius;
};

