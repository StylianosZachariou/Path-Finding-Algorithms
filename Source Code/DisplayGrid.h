#pragma once
#include "SFML/Graphics.hpp"
#include "Grid.h"
#include "Collisions.h"
#include <forward_list>
#include <list>
#include <iostream>

//Class Responsible for Displaying the Grid
class DisplayGrid
{
public:
	DisplayGrid();

	//Collision Function
	void collisionCheck(Coords mouse, Grid& grid, int drawingMode);

	//Display Functions
	void render(sf::RenderWindow*);
	void displayEverything(Grid& grid);
	void resetDislpay();
	void setGridPositions(int rows, int columns, Grid& grid);

private:
	//The distance between the grid lines
	Coords diff;

	//The distance from the edge of the window to the grid
	Coords spaceLeft;

	//Grid
	sf::RectangleShape gridGuidelines;
	Coords gridGuidelinesSize;
	std::forward_list<sf::RectangleShape> gridLines;
	
	//Rectangles
	sf::RectangleShape startRect;
	sf::RectangleShape endRect;
	std::forward_list<sf::RectangleShape> wallRects;
	std::forward_list<sf::RectangleShape> pathRects;
};

