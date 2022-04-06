#pragma once
#include "Grid.h"
//Class Redponsible for Checking Collisions
class Collisions
{
public:
	static bool pointToAABB(Coordsf max, Coordsf min, Coords point); //Collision between a point and a box
};

