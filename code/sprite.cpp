#include "sprite.h"
#include <string>

bool Sprite::loadTexture(std::string path) {
	return this->texture.loadFromFile(path);
}

void Sprite::render(Camera* camera) {
	this->texture.render(this->getPosition().x, this->getPosition().y, camera);

	this->setSize(this->texture.getSize().x,
				this->texture.getSize().y);
}

void Sprite::move(Camera* camera){
	//Move the dot left or right
	
	//this->pPosition.x += this->pVelocity.x;
	this->changeX(this->getVelocity().x);

	//If the dot went too far to the left or right
	if ((this->getPosition().x < 0) ||
		(this->getPosition().x + this->getSize().x > LEVEL_WIDTH))
	{
		//Move back
		this->changeX(-this->getVelocity().x);

	}

	//Move the dot up or down
	this->changeY(this->getVelocity().y);

	//If the dot went too far up or down
	if ((this->getPosition().y < 0) ||
		(this->getPosition().y + this->getSize().y > LEVEL_WIDTH))
	{
		//Move back
		this->changeY(-this->getVelocity().y);
	}

}

Texture* Sprite::getTexture()
{
	return &this->texture;
}

void Sprite::changeX(double x)
{
	this->setPosition(this->getPosition().x + x, this->getPosition().y);
}

void Sprite::changeY(double y)
{
	this->setPosition(this->getPosition().x, this->getPosition().y + y);
}

double Sprite::distance(Sprite* other)
{
	double deltaX = this->getPosition().x - other->getPosition().x;
	double deltaY = this->getPosition().x - other->getPosition().x;

	return sqrt(deltaX * deltaX + deltaY * deltaY);
}