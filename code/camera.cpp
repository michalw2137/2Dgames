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


void Camera::setScale(double scale) {
	this->setSize(this->getSize().x / scale,
					this->getSize().y / scale);
	this->scale = scale;
}

void Camera::setTargetScale(double scale) {
	this->targetScale = scale;
}

void Camera::zoom(double speed) {
	this->scale = (scale*(1. - speed) + targetScale * speed);
}

double Camera::getScale() {
	return this->scale;
}

double Camera::getTargetScale() {
	return this->targetScale;
}

double Camera::getHalfHeight()
{
	return this->getSize().y / 2.0;
}

double Camera::getHalfWidth()
{
	return this->getSize().x / 2.0;
}

bool Camera::isSeen(Movable* object)
{
	double right = this->getPosition().x + this->getSize().x;
	double left = this->getPosition().x;

	double top = this->getPosition().y;
	double bottom = this->getPosition().y + this->getSize().y;

	//printf(" r = %F \n l = %F \n t = %F \n b = %F \n\n", right, left, top, bottom);
	//printf(" x = %F \n y = %F \n\n", object->getPosition().x + scale * object->getSize().x, object->getPosition().y + scale * object->getSize().y);

	if (object->getPosition().x + scale * object->getSize().x > left && 
		object->getPosition().x + scale * object->getSize().x < right &&
		object->getPosition().y + scale * object->getSize().y > top && 
		object->getPosition().y + scale * object->getSize().y < bottom) {
		return true;
	}
	else {
		return false;
	}
}
