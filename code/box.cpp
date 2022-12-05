#include <string>
#include "Box.h"
#include <sstream>

void Box::resolveBoxCollision(Box* other) {
	double r1 = this->getPosition().x;
	double l1 = this->getPosition().x + this->getSize().x;

	double t1 = this->getPosition().y;
	double b1 = this->getPosition().y + this->getSize().y;

	double r2 = other->getPosition().x;
	double l2 = other->getPosition().x + other->getSize().x;

	double t2 = other->getPosition().y;
	double b2 = other->getPosition().y + other->getSize().y;



	double left = r1 - l2;
	double right = r2 - l1;
	double top = b1 - t2;
	double bottom = b2 - t1;

	if (left > 0 && right > 0 && top > 0 && bottom > 0) {
		printf("dupa");
		Vector v = {0, 0};

		left < right ? v.x = -left : v.x = right;
		top < bottom ? v.y = -top : v.y = bottom;

		abs(v.x) < abs(v.y) ? v.y = 0 : v.x = 0;
		/*if (abs(v.x) < abs(v.y)) {
			v.y = 0;
		}
		if (abs(v.x) > abs(v.y)) {
			v.x = 0;
		}*/
		this->changePosition(v);
	}
}