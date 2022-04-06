#include "Collisions.h"

//Check for collision between a box and a point
bool Collisions::pointToAABB(Coordsf max, Coordsf min, Coords point)
{
	//If the point's coords are higher or equal than the min coords of the box
	//And the point's coords are smaller or equal than the max coords of the box
	if ((point.x >= min.x) && (point.x <= max.x) &&
		(point.y >= min.y) && (point.y <= max.y))
	{
		return true; //Collision Occurs
	}
	else
	{
		return false; //Collision does not occur
	}

}