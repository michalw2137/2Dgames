#pragma once
#include <SDL.h>
#include <string>
#include "globals.h"

class Texture {
public:
	Texture();
	~Texture();
	void free();

	bool loadFromFile(std::string path);

	void render();

	void accelerate();

	void accelerateTowardsTarget();

	void move();

	void buttonDown(SDL_Event* e, double speed);

	void buttonUp(SDL_Event* e);

	//setters
	void setAlpha(Uint8 alpha);

	void setTargetPosition(double x, double y);

	void setPosition(double x, double y);

	void setAcceleration(double a);

	//getters
	Vector getSize();

	Vector getPosition();

	Vector getTargetPosition();

	Vector getVelocity();

	Vector getTargetVelocity();

	SDL_Texture* getTexture();

private:
	SDL_Texture* pTexture;
	SDL_Rect pRenderRect;

	double acceleration;

	Vector pSize;
	Vector pPosition;
	Vector pVelocity;
	Vector pTargetVelocity;
	Vector pTargetPosition;

};
