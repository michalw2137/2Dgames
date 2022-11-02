#pragma once
#include <SDL.h>
#include <string>
#include "globals.h"
#include "camera.h"

class Texture {
public:
	Texture();
	~Texture();
	void free();

	bool loadFromFile(std::string path);

	void render(double x, double y, Camera* camera);

	//setters
	void setAlpha(Uint8 alpha);

	void setSize(double x, double y);

	void setPosition(double x, double y);

	//getters
	Vector getSize();

	Vector getPosition();

	SDL_Texture* getTexture();

private:
	SDL_Texture* pTexture;
	SDL_Rect pRenderRect;

	Vector pSize;
	Vector pPosition;
};
