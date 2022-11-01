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

	Texture* getTexture();
private:
	Texture texture;

};
