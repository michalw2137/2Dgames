#include <string>
#include "Box.h"
#include <sstream>

void Box::resolveBoxCollision(Box* wall) {
	double l1 = this->getPosition().x - this->getSize().x / 2.0;
	double r1 = this->getPosition().x + this->getSize().x - this->getSize().x / 2.0;

	double t1 = this->getPosition().y - this->getSize().y / 2.0;
	double b1 = this->getPosition().y + this->getSize().y - this->getSize().y / 2.0;

	double l2 = wall->getPosition().x;
	double r2 = wall->getPosition().x + wall->getSize().x;

	double t2 = wall->getPosition().y;
	double b2 = wall->getPosition().y + wall->getSize().y;

	//printf("box1 r,l,t,b:  %F, %F, %F, %F \n", r1, l1, t1, b1);
	//printf("box2 r,l,t,b:  %F, %F, %F, %F \n", r2, l2, t2, b2);

	double left = r1 - l2;
	double right = r2 - l1;
	double top = b1 - t2;
	double bottom = b2 - t1;

	//printf("left = %F   \n", left);
	//printf("right = %F  \n", right);
	//printf("top = %F    \n", top);
	//printf("bottom = %F \n", bottom);
	//printf("l,r,t,b:  %F, %F, %F, %F \n", left, right, top, bottom);

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