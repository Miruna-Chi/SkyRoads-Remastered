#pragma once
#include <iostream>
#include <cmath>
#include <tuple>
#include <Core/Engine.h>
#define _USE_MATH_DEFINES

class Sphere
{
public: 
	Mesh* sphere;
	std::string name;
	int stackCount;
	int sectorCount;

	Sphere();
	Sphere(glm::vec3 center, int stackCount, int sectorCount, std::string name);
	Mesh* CreateSphere(glm::vec3 center, int stackCount, int sectorCount, std::string name);
	// creates a sphere (by dividing it by sectors(longitude) and stacks(latitude))
	// Radius = 1.00
};

