#include "camera.h"
#include "globals.h"

Camera::Camera() {
	this->setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
}

Camera::~Camera() {

}

void Camera::positionInMiddle(double x, double y, double width, double height) {
	double tempX = (x + width / 2.0f) - WINDOW_WIDTH / 2.0f;
	double tempY = (y + height / 2.0f) - WINDOW_HEIGHT / 2.0f;
	this->setPosition(tempX, tempY);
}


void Camera::keepInBounds() {
	if (this->getPosition().x < 0)
	{	
		this->setX(0);
	}	
	if (this->getPosition().y < 0)
	{	
		this->setY(0);
	}
	if (this->getPosition().x > LEVEL_WIDTH - this->getSize().x)
	{	
		this->setX(LEVEL_WIDTH - this->getSize().x);
	}	
	if (this->getPosition().y > LEVEL_HEIGHT - this->getSize().y)
	{	
		this->setX(LEVEL_HEIGHT - this->getSize().y);
	}
}

void Camera::setX(double x)
{
	this->setPosition(x, this->getPosition().y);
}

void Camera::setY(double y)
{
	this->setPosition(this->getPosition().x, y);
}

