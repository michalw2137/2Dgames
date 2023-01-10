#pragma once
#include <SDL.h>
#include <string>
#include "globals.h"
#include <fstream>
#include <sstream>
#include "texture.h"
#include <vector>
#include "box.h"
#include "ball.h"

class Level
{
public:
	Level();
	~Level();
	void free();

	void loadLevel(std::string path, int width, int height);

	void renderLevel(Camera* camera);

	void resolveWallCollisions(Ball* ball);
	void resolveWallCollisions(Box* box);
	void changeX(double x);

	bool touchesWall(Vector position);

	int getHeight();
	int getWidth();

private:
	bool loadLevelFromFile(std::string path, int width, int height);
	bool loadTextures();

	Vector offset = { 0,0 };

	int width, height;

	std::vector<Box> walls;

	std::string layout;
	Texture textures[TEXTURES_SIZE];

	std::string texturesPaths[TEXTURES_SIZE] = {
		"textures/water.png",
		"textures/air.png",
		"textures/stone.png",
		"textures/brick.png",
		"textures/fire.png",

		"textures/ground.png",
		"textures/tree.png",
		"textures/tree_top.png",
		"textures/left_slope.png",
		"textures/middle.png",
		"textures/right_slope.png",
		"textures/cloud.png",
	};

};

