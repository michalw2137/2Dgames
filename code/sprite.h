#pragma once
#include <SDL.h>
#include <string>
#include "globals.h"
#include "movable.h"
#include "texture.h"

class Sprite: public Movable {

public:
	bool loadTexture(std::string path);
	void render(Camera* camera);
	void move(Camera* camera);

	void size(double x, double y);
	Texture* getTexture();

	double distance(Sprite* other);

	void setVelocityX(double x);
	void setVelocityY(double y);

private:
	Texture texture;
	void changeX(double x);
	void changeY(double y);
};

