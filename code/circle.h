#pragma once
#include <SDL.h>
#include <string>
#include "globals.h"
#include "sprite.h"

class Circle: public Sprite{

public:

	void resolveCollision(Circle* other);

	void bounceIfOnEdge();

	double getRadius();
	void setRadius(double r);

private:
	double mass = 1;
	double radius;
};

