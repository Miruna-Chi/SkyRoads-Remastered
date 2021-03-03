#include "Decoration.h"

Decoration::Decoration(std::string texture, float x, float y, float z, float sf) {
	this->texture = texture;
	this->x = x;
	this->y = y;
	this->z = z;
	this->sf = sf;
}