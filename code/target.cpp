#include "target.h"
#include <iostream>

bool Target::checkForCollision(Sprite* sprite)
{
	if (gl::length(gl::vector(this->getPosition(), sprite->getPosition())) < detectionRadius) {
		//std::cout << sprite << " collided with target \n";

		return true;
	}
	return false;
}

