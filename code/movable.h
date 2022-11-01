#pragma once
#include <SDL.h>
#include <string>
#include "globals.h"

class Movable {

public:
	Movable();
	~Movable();
	void free();

	void accelerate();

	void accelerateTowardsTarget();

	void move();

	void buttonDown(SDL_Event* e, double speed);

	void buttonUp(SDL_Event* e);

	//setters
	void setSize(double x, double y);

	void setTargetPosition(double x, double y);

	void setPosition(double x, double y);

	void setAcceleration(double a);

	//getters
	Vector getSize();

	Vector getPosition();

	Vector getTargetPosition();

	Vector getVelocity();

	Vector getTargetVelocity();

private:

	double acceleration;

	Vector pSize;
	Vector pPosition;
	Vector pVelocity;
	Vector pTargetVelocity;
	Vector pTargetPosition;
};
