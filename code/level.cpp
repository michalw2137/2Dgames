#include "level.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "camera.h"
#include "sprite.h"

Level::Level() {
}

Level::~Level() {
	this->free();
}

void Level::free() {
	if (this == NULL) {
		printf("null pointer \n");
		return;
	}

}

void Level::loadLevel(std::string path, int width, int height) {
	bool file = loadLevelFromFile(path, width, height);
	bool textures = loadTextures();
	if (!file) {
		throw "failed to load level layout from " + path;
	}
	if (!textures) {
		throw "failed to load tile textures \n";
	}
}

bool Level::loadLevelFromFile(std::string path, int width, int height) {
	this->width = width;
	this->height = height;

	std::ifstream fTemp;
	std::stringstream sTemp;
	fTemp.open(path);
	if (fTemp.is_open()) {
		sTemp << fTemp.rdbuf();

		//std::cout << sTemp.str() << '\n';
		this->layout = sTemp.str();

		fTemp.close();
		sTemp.clear();
		return true;
	}
	else {
		return false;
	}
}

bool Level::loadTextures() {
	for (int i = 0; i < TEXTURES_SIZE; i++) {
		if (!textures[i].loadFromFile(texturesPaths[i])) {
			printf("failed to load %s !\n", texturesPaths[i].c_str());
			return false;
		}
		textures[i].setSize(50, 50);
	}

	int i = 0;
	for (int y = 0; y < height * 50; y += 50) {
		for (int x = 0; x < width * 50; x += 50) {
			if (this->layout.at(i) == '\n') {
				i++;
			}

			if (this->layout.at(i) == 'x') {
				//printf("wall at %d, %d\n", x, y);
				Box wall;
				wall.setPosition(x, y);
				wall.setSize(50, 50);
				walls.push_back(wall);

			}
			
			i++;
		}
	}

	return true;
}

void Level::renderLevel(Camera* camera) {
	int i = 0;
	for (int y = 0; y < height * 50; y += 50) {
		for (int x = 0; x < width * 50; x += 50) {

			if (this->layout.at(i) == '\n') {
				i++;
			}

			switch (this->layout.at(i)) {
			case 'f':
				textures[TEXTURES_FIRE].render(x, y, camera);
				break;

			case 'x':
				textures[TEXTURES_STONE].render(x, y, camera);
				break;

			case 'b':
				textures[TEXTURES_BRICK].render(x, y, camera);
				break;

			case 'w':
				textures[TEXTURES_WATER].render(x, y, camera);
				break;

			case '.':
				//textures[TEXTURES_AIR].setAlpha(255 / 2);

				textures[TEXTURES_AIR].render(x, y, camera);
				break;

			case ' ':
				break;

			case '\n':
				break;

			default:
				printf("UNKNOWN CHARACTER \n");
				break;
			}
			i++;
		}
	}
	//printf("level loaded \n\n");
}

void Level::resolveWallCollisions(Box* box) {
	for  (Box wall : walls) {
		//printf("next wall:\n");
		box->resolveBoxCollision(&wall);
	}
	//printf("all walls \n\n");
}

void Level::resolveWallCollisions(Ball* ball) {
	for (Box wall : walls) {
		//printf("next wall:\n");
		ball->resolveBoxCollision(&wall);
	}
	//printf("all walls \n\n");
}

bool Level::touchesWall(Vector position) {
	for (Box wall : walls) {
		if (wall.getPosition() == position) {
			return true;
		}
	}
	return false;
}

int Level::getHeight()
{
	return height;
}

int Level::getWidth()
{
	return width;
}
