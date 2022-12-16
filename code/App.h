#pragma once
#ifndef APP_H // include guard
#define APP_H

#include "camera.h"
#include "box.h"
#include "ball.h"
#include "target.h"
#include "level.h"
#include "screen.h"
#include "globals.h"

#include <SDL.h>
#include <SDL_image.h>

namespace App {
	
	bool loadTextures();

	void setRandomPosition(Sprite* sprite);
	void resetLevel();


	void setup();

	void loop();

};

#endif