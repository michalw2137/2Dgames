#include <string>
#include "ball.h"
#include <sstream>

void Ball::resolveCollision(Ball* other)
{
    double newX1, newX2, newY1, newY2;

    newX1 = (this->getVelocity().x * (this->mass - other->mass) / (this->mass + other->mass) + (2 * other->mass * other->getVelocity().x) / (this->mass + other->mass));
    newY1 = (this->getVelocity().y * (this->mass - other->mass) / (this->mass + other->mass) + (2 * other->mass * other->getVelocity().y) / (this->mass + other->mass));

    newX2 = (other->getVelocity().x * (other->mass - this->mass) / (this->mass + other->mass) + (2 * this->mass * this->getVelocity().x) / (this->mass + other->mass));
    newY2 = (other->getVelocity().y * (other->mass - this->mass) / (this->mass + other->mass) + (2 * this->mass * this->getVelocity().y) / (this->mass + other->mass));


    //printf("\nBalls before collision: \n %s \n %s \n\n", this->str().c_str(), other->str().c_str());
    
    //printf("distance = %F \n\n", this->distance(other));
    this->setVelocity(newX1, newY1); 
    other->setVelocity(newX2, newY2);

    //printf("Balls after collision: \n %s \n %s \n\n", this->str().c_str(), other->str().c_str());

}

void Ball::separate(Ball* other)
{
    Vector vec = gl::vector(this->getPosition(), other->getPosition());
    Vector normalised = gl::normalise(vec);
    double scale = this->getRadius() + other->getRadius() - gl::length(vec);

    Vector separation = gl::scale(normalised, scale);


    //printf("delta = (%F, %F) \n", vec.x, vec.y);
    //printf("normalised = (%F, %F) \n", normalised.x, normalised.y);
    //printf("normalised  length = (%F) \n", gl::length(normalised));
    //printf("scale = (%F) \n", scale);
    //printf("separation vector = (%F, %F) \n\n", separation.x, separation.y);
    //
    //printf("\nBalls before collision: \n %s \n %s \n\n", this->str().c_str(), other->str().c_str());
    //
    //printf("distance = %F \n", this->distance(other));

    this->changePosition(separation);
    other->changePosition(gl::scale(separation, -1));

    //printf("Balls after collision: \n %s \n %s \n\n", this->str().c_str(), other->str().c_str());


}

void Ball::bounceIfOnEdge()
{
    if (this->getPosition().x <= this->radius)            // hit left edge, go right
    {
        this->setVelocityX(abs(this->getVelocity().x));
    }
    if (this->getPosition().x >= WINDOW_WIDTH - this->radius)    // hit right edge, go left
    {
        this->setVelocityX(-abs(this->getVelocity().x));
    }

    if (this->getPosition().y <= this->radius)            // hit bottom edge, go up
    {
        this->setVelocityY(abs(this->getVelocity().y));
    }
    if (this->getPosition().y >= WINDOW_HEIGHT - this->radius)   // hit top edge, go down
    {
        this->setVelocityY(-abs(this->getVelocity().y));
    }

    
}

double Ball::getRadius()
{
	return radius;
}

void Ball::setRadius(double r)
{
	this->radius = r;
	this->size(r * 2.0, r * 2.0);
}

std::string Ball::str()
{
    std::stringstream ss;
    ss << "r = "
        << this->getRadius()
        << ", pos: ["
        << this->getPosition().x
        << ", "
        << this->getPosition().y
        << "], vel: "
        << this->getVelocity().x
        << ", "
        << this->getVelocity().y;
    return ss.str();
}
