#pragma once
#include <SDL.h>
#include <string>
#include "globals.h"
#include "sprite.h"
#include "box.h"

class Screen{

public:
	bool loadTextures();

	void boxWins();
	void ballWins();
	void gameOver();
	void emptyScreen();

	void render();

	int getWait();
private:
	int time = 0;
	Texture box, ball, over, empty, *currentTexture;
};

