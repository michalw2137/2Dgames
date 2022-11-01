#include "camera.h"
#include "globals.h"

Camera::Camera() {
	this->setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
}

Camera::~Camera() {

}

void Camera::setX(double x)
{
	this->setPosition(x, this->getPosition().y);
}

void Camera::setY(double y)
{
	this->setPosition(this->getPosition().x, y);
}

