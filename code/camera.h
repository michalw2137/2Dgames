#pragma once
#include "globals.h"

class Camera {
public:
	Camera();

	~Camera();

	void positionInMiddle(double x, double y, double width, double height);

	void keepInBounds();

	Vector getPosition();

private:

	double width;
	double height;

	double x;
	double y;
};