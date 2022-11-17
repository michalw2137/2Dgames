#pragma once
#include <SDL.h>
#include <string>
#include "sprite.h"

class Button : public Sprite{

public:

	bool loadTextures(std::string on_path, std::string off_path);

	void mouseClicked(int mouseX, int mouseY, bool* flag);

	void changeSize(double x, double y);

private:
	bool isClicked(int mouseX, int mouseY);

	void changeState();
	bool state = true;
	Texture onTexture;
	Texture offTexture;

};
