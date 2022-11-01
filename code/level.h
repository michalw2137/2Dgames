#pragma once
#include <SDL.h>
#include <string>
#include "globals.h"
#include <fstream>
#include <sstream>
#include "texture.h"

class Level
{
public:
	Level();
	~Level();
	void free();

	bool laodLevelFromFile(std::string path);

	bool loadTextures();

	void renderLevel(Camera* camera);

	
private:
	std::string layout;
	Texture textures[TEXTURES_SIZE];

	std::string texturesPaths[TEXTURES_SIZE] = {
		"textures/water.png",
		"textures/air.png",
		"textures/stone.png",
		"textures/brick.png",
		"textures/fire.png"
	};

};

