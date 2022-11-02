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

	Texture* getTexture();

	double distance(Sprite* other);

private:
	Texture texture;
	void changeX(double x);
	void changeY(double y);
};

