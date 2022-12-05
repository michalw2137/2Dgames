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

void Movable::accelerate() {
	this->pVelocity.x = this->pVelocity.x * acceleration + this->pTargetVelocity.x * (1 - acceleration);
	this->pVelocity.y = this->pVelocity.y * acceleration + this->pTargetVelocity.y * (1 - acceleration);
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

void Movable::arrowDown(SDL_Event* e, double speed) {
	switch (e->key.keysym.sym) {
	case SDLK_UP:
		this->pTargetVelocity.y = -speed;
		break;

	case SDLK_DOWN:
		this->pTargetVelocity.y = speed;
		break;

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
	switch (e->key.keysym.sym) {
	case SDLK_UP:
		this->pTargetVelocity.y = 0;
		break;

	case SDLK_DOWN:
		this->pTargetVelocity.y = 0;
		break;

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
	switch (e->key.keysym.sym) {
	case SDLK_w:
		this->pTargetVelocity.y = -speed;
		break;

	case SDLK_s:
		this->pTargetVelocity.y = speed;
		break;

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
	switch (e->key.keysym.sym) {
	case SDLK_w:
		this->pTargetVelocity.y = 0;
		break;

	case SDLK_s:
		this->pTargetVelocity.y = 0;
		break;

	case SDLK_a:
		this->pTargetVelocity.x = 0;
		break;

	case SDLK_d:
		this->pTargetVelocity.x = 0;
		break;

	default: break;
	}
}

void Movable::changePosition(Vector delta)
{
	this->pPosition.x += delta.x;
	this->pPosition.y += delta.y;
}


void Movable::setTargetPosition(double x, double y) {
	this->pTargetPosition.x = x;
	this->pTargetPosition.y = y;
}

void Movable::setAcceleration(double a) {
	acceleration = a;
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



