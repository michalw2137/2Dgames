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

Texture* Sprite::getTexture()
{
	return &this->texture;
}
