#include "globals.h"

Vector gl::vector(Vector position1, Vector position2)
{
	double x = position1.x - position2.x;
	double y = position1.y - position2.y;
	return { x, y };
}

Vector gl::scale(Vector vec, double scale)
{
	double x = vec.x * scale;
	double y = vec.y * scale;
	return { x, y };
}

Vector gl::normalise(Vector vec)
{
	double x = vec.x / length(vec);
	double y = vec.x / length(vec);
	return { x, y };
}

double gl::length(Vector vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

double gl::clamp(double x, double min, double max) {
	if (min > max) {
		double temp = max;
		max = min;
		min = temp;
	}
	if (x < min) {
		return min;
	}
	else if (x > max) {
		return max;
	} else {
		return x;
	}
}

