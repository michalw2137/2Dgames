#pragma once
#include <SDL.h>
#include <string>
#include "globals.h"
#include "sprite.h"
#include "box.h"

class Target: public Box{

public:
	bool checkForCollision(Sprite* sprite);

	int getCurrentLevel();

private:
	int currentLevel = 0;
	double detectionRadius = 50;
};

