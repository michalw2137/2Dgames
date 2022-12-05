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

	void arrowDown(SDL_Event* e, double speed);

	void arrowUp(SDL_Event* e);

	void wsadDown(SDL_Event* e, double speed);

	void wsadUp(SDL_Event* e);


	//changers
	void changePosition(Vector delta);

	//setters
	void setSize(Vector size);

	void setSize(double x, double y);

	void setTargetPosition(double x, double y);

	void setPosition(double x, double y);

	void setAcceleration(double a);

	void setVelocity(double x, double y);

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
