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

	bool loadLevelFromFile(std::string path, int width, int height);

	bool loadTextures();

	void renderLevel(Camera* camera);

	
private:
	int width, height;

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

