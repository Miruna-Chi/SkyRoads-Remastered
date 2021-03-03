#pragma once
#include <iostream>

class Decoration
{
	public:
		float x;
		float y;
		float z;
		float sf;
		bool collided = false;
		float rotation_angle = 0;
		std::string texture;
		std::string color;

		Decoration(std::string texture, float x, float y, float z, float sf);
};

