#include <SDL_image.h>
#include <iostream>
#include "movable.h"
#include "globals.h"

Movable::Movable() {
	this->pSize = { 0, 0 };
	this->pPosition = { 0, 0 };

	this->acceleration = 0;
	this->pVelocity = { 0, 0 };
	this->pTargetVelocity = { 0, 0 };
	this->pTargetPosition = { 0,0 };
}

Movable::~Movable() {
	free();
}

void Movable::free() {
	this->acceleration = 0;
	this->pVelocity = { 0, 0 };
	this->pTargetVelocity = { 0, 0 };
	this->pTargetPosition = { 0,0 };
}

Vector f(Vector pos) {
	return { 0, 0 };
}

void Movable::boost() {
	if (!isBoosted) {
		return;
	}
	if (boostFrames >= maxBoostFrames) {
		return;
	}
	boostFrames++;
	printf("increasing jump strength \n");
}

void Movable::accelerate(double deltaTime, Vector gravity) {
	if (pVelocity.y == 0) {
		airborne = false;
		jumpsLeft = maxJumps;
	}
	if (!airborne) {
		//this->pVelocity.x = this->pVelocity.x * acceleration + this->pTargetVelocity.x * (1 - acceleration);
		pVelocity.x = pTargetVelocity.x;
	}
	if (deltaTime > 30) {
		deltaTime = 30;
	}
	Vector real_gravity;
	if (pVelocity.y > 0.0001) {
		//printf("increasing gravity \n");
		real_gravity = {0, 3.*GRAVITY};
	}
	else {
		real_gravity = { 0, GRAVITY };
	}
	//std::cout << "airborne = " << airborne << '\n';

	pPosition += pVelocity * deltaTime + real_gravity * deltaTime * deltaTime / 2.0;
	pVelocity += real_gravity * deltaTime;


	// LARP movement
	//this->pVelocity.x = this->pVelocity.x * acceleration + this->pTargetVelocity.x * (1 - acceleration);
	//this->pVelocity.y = this->pVelocity.y * acceleration + this->pTargetVelocity.y * (1 - acceleration);
}



void Movable::accelerateTowardsTarget() {
	//printf("camera position: (%F, %F) \n", pPosition.x, pPosition.y);
	//printf("camera target: (%F, %F) \n", pTargetPosition.x, pTargetPosition.y);
	this->pVelocity.x = (this->pTargetPosition.x - this->pPosition.x - (this->pSize.x / 2.)) / 20.;
	this->pVelocity.y = (this->pTargetPosition.y - this->pPosition.y - (this->pSize.y / 2.)) / 20.;
	//printf("camera speed: (%F, %F) \n\n", pVelocity.x, pVelocity.y);

}

void Movable::move() {
	//Move the dot left or right
	this->pPosition.x += this->pVelocity.x;

	//If the dot went too far to the left or right
	if ((this->pPosition.x < 0) ||
		(this->pPosition.x + this->pSize.x > LEVEL_WIDTH))
	{
		//Move back
		this->pPosition.x -= this->pVelocity.x;
	}

	//Move the dot up or down
	this->pPosition.y += this->pVelocity.y;

	//If the dot went too far up or down
	if ((this->pPosition.y < 0) ||
		(this->pPosition.y + this->pSize.y > LEVEL_WIDTH))
	{
		//Move back
		this->pPosition.y -= this->pVelocity.y;
	}
}

void Movable::jump(double startingVelocity) {
	/*if (airborne) {
		return;
	}*/
	airborne = true;
	jumpsLeft--;
	pVelocity.y = -startingVelocity * (1 + boostFrames/maxBoostFrames/2.);
	boostFrames = 0;
	setBoosted(false);
	printf("jumping \n");
}

bool Movable::canJump() {
	return jumpsLeft > 0;
}

void Movable::arrowDown(SDL_Event* e, double speed) {
	//if (abs(pVelocity.y) < 0.001) {
	//	airborne = false;
	//}
	//if (airborne) {
	//	return;
	//}
	switch (e->key.keysym.sym) {
	/*case SDLK_UP:
		if(e->key.repeat == 0)
			this->jump(jumpForce);
		break;*/

	/*case SDLK_DOWN:
		this->pTargetVelocity.y = speed;
		break;*/

	case SDLK_LEFT:
		this->pTargetVelocity.x = -speed;
		break;

	case SDLK_RIGHT:
		this->pTargetVelocity.x = speed;
		break;

	default: break;
	}
}

void Movable::arrowUp(SDL_Event* e) {
	//if (airborne) {
	//	return;
	//}
	switch (e->key.keysym.sym) {
	/*case SDLK_UP:
		this->pTargetVelocity.y = 0;
		break;

	case SDLK_DOWN:
		this->pTargetVelocity.y = 0;
		break;*/

	case SDLK_LEFT:
		this->pTargetVelocity.x = 0;
		break;

	case SDLK_RIGHT:
		this->pTargetVelocity.x = 0;
		break;

	default: break;
	}
}

void Movable::wsadDown(SDL_Event* e, double speed) {
	//if (abs(pVelocity.y) < 0.001) {
	//	airborne = false;
	//}
	//if (airborne) {
	//	return;
	//}
	switch (e->key.keysym.sym) {
	/*case SDLK_w:
		if (e->key.repeat == 0)
			this->jump();
		break;*/

	/*case SDLK_s:
		this->pTargetVelocity.y = speed;
		break;*/

	case SDLK_a:
		this->pTargetVelocity.x = -speed;
		break;

	case SDLK_d:
		this->pTargetVelocity.x = speed;
		break;

	default: break;
	}
}

void Movable::wsadUp(SDL_Event* e) {
	//if (airborne) {
	//	return;
	//}
	switch (e->key.keysym.sym) {
	/*case SDLK_w:
		this->pTargetVelocity.y = 0;
		break;

	case SDLK_s:
		this->pTargetVelocity.y = 0;
		break;*/

	case SDLK_a:
		this->pTargetVelocity.x = 0;
		break;

	case SDLK_d:
		this->pTargetVelocity.x = 0;
		break;

	default: break;
	}
}

void Movable::changeX(double delta)
{
	this->pPosition.x += delta;
}

void Movable::changeY(double delta)
{
	this->pPosition.y += delta;
}

void Movable::changePosition(Vector delta)
{
	this->pPosition.x += delta.x;
	this->pPosition.y += delta.y;
}

void Movable::setBoosted(bool boosted) {
	this->isBoosted = boosted;
}

void Movable::setAirborne(bool airborne) {
	this->airborne = airborne;
}

void Movable::setTargetPosition(double x, double y) {
	this->pTargetPosition.x = x;
	this->pTargetPosition.y = y;
}

void Movable::setAcceleration(double x, double y) {
	pAcceleration = { x, y };
}

void Movable::setVelocity(double x, double y)
{
	this->pVelocity = { x, y };
}

void Movable::setPosition(double x, double y) {
	this->pPosition = { x, y };
}

void Movable::setSize(Vector size) {
	this->pSize = size;
}

void Movable::setSize(double x, double y) {
	this->pSize.x = x;
	this->pSize.y = y;
}

bool Movable::getAirborne() {
	return this->airborne;
}

Vector Movable::getSize() {
	return this->pSize;
}

Vector Movable::getPosition() {
	return this->pPosition;
}

Vector Movable::getTargetPosition() {
	return this->pTargetPosition;
}

Vector Movable::getVelocity() {
	return this->pVelocity;
}

Vector Movable::getTargetVelocity() {
	return this->pTargetVelocity;
}



