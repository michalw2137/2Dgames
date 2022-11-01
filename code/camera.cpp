#include "camera.h"
#include "globals.h"

Camera::Camera() {
	this->width = WINDOW_WIDTH;
	this->height = WINDOW_HEIGHT;
	this->x = 0;
	this->y = 0;
}

Camera::~Camera() {

}

void Camera::positionInMiddle(double x, double y, double width, double height) {
	this->x = (x + width / 2.0f) - WINDOW_WIDTH / 2.0f;
	this->y = (y + height / 2.0f) - WINDOW_HEIGHT / 2.0f;
}


void Camera::keepInBounds() {
	if (this->x < 0)
	{	
		this->x = 0;
	}	
	if (this->y < 0)
	{	
		this->y = 0;
	}	
	if (this->x > LEVEL_WIDTH - this->width)
	{	
		this->x = LEVEL_WIDTH - this->width;
	}	
	if (this->y > LEVEL_HEIGHT - this->height)
	{	
		this->y = LEVEL_HEIGHT - this->height;
	}
}

Vector Camera::getPosition()
{
	return {this->x, this->y};
}

