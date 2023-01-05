#pragma once
#include "globals.h"
#include "movable.h"

class Camera : public Movable{
public:
	Camera();

	~Camera();

	void setScale(double scale);
	void setTargetScale(double scale);
	void zoom(double speed);

	void moveTo(double x, double y);

	double getScale();
	double getTargetScale();

	double getHalfHeight();
	double getHalfWidth();

	Vector getDelta();

	bool isSeen(Movable* sprite, bool print = false);
private:
	Vector lastPosition = {0,0};
	Vector deltaPosition = {0,0};
	double scale;
	double targetScale;
	void setX(double x);
	void setY(double y);
};