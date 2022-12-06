#include "target.h"
#include <iostream>

bool Target::checkForCollision(Sprite* sprite)
{
	if (gl::length(gl::vector(this->getPosition(), sprite->getPosition())) < detectionRadius) {
		std::cout << sprite << "collided with target \n";

		currentLevel++;
		if (currentLevel >= LEVELS) {
			currentLevel = 0;
		}

		return true;
	}
	return false;
}

int Target::getCurrentLevel()
{
	return currentLevel;
}
