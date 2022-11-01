#pragma once
#include "globals.h"
#include "movable.h"

class Camera : public Movable{
public:
	Camera();

	~Camera();

private:
	void setX(double x);
	void setY(double y);
};