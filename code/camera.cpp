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

//void Camera::accelerateTowardsTarget() {
//	printf("camera position: (%F, %F) \n", getPosition().x, getPosition().y);
//	printf("camera target: (%F, %F) \n", getTargetPosition().x, getTargetPosition().y);
//	double tempX = (this->getTargetPosition().x - this->getPosition().x - WINDOW_WIDTH) / 20.;
//	double tempY = (this->getTargetPosition().y - this->getPosition().y - WINDOW_HEIGHT) / 20.;
//	setVelocity(tempX, tempY);
//
//
//}