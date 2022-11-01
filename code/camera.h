#pragma once
#include "globals.h"
#include "movable.h"

class Camera : public Movable{
public:
	Camera();

	~Camera();

	void positionInMiddle(double x, double y, double width, double height);

	void keepInBounds();


private:
	void setX(double x);
	void setY(double y);
};