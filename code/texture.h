#pragma once
#include <SDL.h>
#include <string>


class Texture {
public:
	//Initializes variables
	Texture();

	//Deallocates memory
	~Texture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

	//Deallocates texture
	void free();

	//Renders texture at given point
	void render();

	void setPosition(double x, double y);

	void setAcceleration(double a);


	void setXVelocity(double velocity);
	void setYVelocity(double velocity);

	void setXTargetVelocity(double velocity);
	void setYTargetVelocity(double velocity);

	void accelerate();

	void move();

	void setAlpha(Uint8 alpha);
	
	void setTarget(double x, double y);

	void accelerateTowardsTarget();

	void buttonDown(SDL_Event* e, double speed);
	void buttonUp(SDL_Event* e);


	//Gets image dimensions
	int getWidth();
	int getHeight();

	int getXPosition();
	int getYPosition();

	double getXVelocity();
	double getYVelocity();

	SDL_Texture* getTexture();

private:
	SDL_Texture* pTexture;

	double pWidth;
	double pHeight;

	double pXPosition;
	double pYPosition;

	double pXVelocity;
	double pYVelocity;

	double pTargetX;
	double pTargetY;

	double pXTargetVelocity;
	double pYTargetVelocity;

	double acceleration;

	SDL_Rect pRenderRect;
};
