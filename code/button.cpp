#include <SDL_image.h>
#include <iostream>
#include "button.h"

bool Button::loadTextures(std::string on_path, std::string off_path)
{
	bool t1 = onTexture.loadFromFile(on_path);
	bool t2 = offTexture.loadFromFile(off_path);

	if (!(t1 && t2)) {
		return false;
	}

	onTexture.setAlpha(128);
	offTexture.setAlpha(128);

	this->setSize(onTexture.getSize());

	this->state = true;
	this->changeState();
	
	return true;
}

void Button::mouseClicked(int mouseX, int mouseY, bool* flag) {
	if (this->isClicked(mouseX, mouseY)) {
		changeState();
		*flag = state;
	}
}

void Button::changeState()
{
	if (state) {
		state = false;
		this->setTexture(&offTexture);
	}
	else {
		state = true;
		this->setTexture(&onTexture);

	}
}

void Button::changeSize(double x, double y)
{
	this->size(x, y);
	this->onTexture.setSize(x, y);
	this->offTexture.setSize(x, y);

}

bool Button::isClicked(int mouseX, int mouseY)
{
	double w = this->getSize().x / 2.0;
	double h = this->getSize().y / 2.0;

	printf("\nmouseX = %d; range X: [%F, %F] \n", mouseX, this->getPosition().x - w, this->getPosition().x + w);
	printf("mouseY = %d; range Y: [%F, %F] \n", mouseY, this->getPosition().y - h, this->getPosition().y + h);

	if (mouseX >= this->getPosition().x - w && mouseX <= this->getPosition().x + w &&
		mouseY >= this->getPosition().y - h && mouseY <= this->getPosition().y + h)
	{
		printf("clicked \n");
		return true;
	}
	else {
		return false;
	}
}



