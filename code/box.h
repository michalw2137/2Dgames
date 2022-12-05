#pragma once
#include <SDL.h>
#include <string>
#include "globals.h"
#include "sprite.h"

class Box : public Sprite {

public:

	void resolveBoxCollision(Box* other);

private:
	double mass = 1;
	double radius;
};

