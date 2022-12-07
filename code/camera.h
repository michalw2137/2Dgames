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
	double getScale();
	double getTargetScale();

	double getHalfHeight();
	double getHalfWidth();

	bool isSeen(Movable* sprite);
private:
	double scale;
	double targetScale;
	void setX(double x);
	void setY(double y);
};