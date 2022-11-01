#include "level.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "camera.h"

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
	/*if (this->air != NULL) {
		SDL_DestroyTexture(air);
		this->air = NULL;
	}
	if (this->stone != NULL) {
		SDL_DestroyTexture(stone);
		this->stone = NULL;
	}
	if (this->brick != NULL) {
		SDL_DestroyTexture(brick);
		this->brick = NULL;
	}
	if (this->fire != NULL) {
		SDL_DestroyTexture(fire);
		this->fire = NULL;
	}
	if (this->water != NULL) {
		SDL_DestroyTexture(water);
		this->water = NULL;
	}*/
}

bool Level::laodLevelFromFile(std::string path) {
	std::ifstream fTemp;
	std::stringstream sTemp;
	fTemp.open(path);
	if (fTemp.is_open()) {
		sTemp << fTemp.rdbuf();

		std::cout << sTemp.str() << '\n';
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
	}

	return true;
}

void Level::renderLevel(Camera* camera) {
	int i = 0;
	for (int y = 0; y < LEVEL_HEIGHT; y += 100) {
		for (int x = 0; x < LEVEL_WIDTH; x += 100) {

			if (this->layout.at(i) == '\n') {
				i++;
			}

			switch (this->layout.at(i)) {
			case 'f':
				textures[TEXTURES_FIRE].render(x, y, camera);
				break;

			case 's':
				textures[TEXTURES_STONE].render(x, y, camera);
				break;

			case 'b':
				textures[TEXTURES_BRICK].render(x, y, camera);
				break;

			case 'w':
				textures[TEXTURES_WATER].render(x, y, camera);
				break;

			case ' ':
				textures[TEXTURES_AIR].setAlpha(255 / 2);

				textures[TEXTURES_AIR].render(x, y, camera);
				break;

			case 'v':
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