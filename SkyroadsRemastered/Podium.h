#pragma once
#include <iostream>

class Podium
{
public:
	float x;
	float y;
	float z;
	bool collided = false;
	std::string color;

	Podium(std::string color, float x, float y, float z);
};

