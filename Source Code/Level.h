#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Input.h"
#include "DisplayGrid.h"
#include "Grid.h"
#include "Collisions.h"
#include "Astar.h"
#include "Lee.h"

//Level Class Responsible 
class Level {
public:

	Level(sf::RenderWindow* hwnd, Input* in);

	//Functions for "Game Loop"
	void handleInput();
	void render();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	
	//Grid
	Grid grid;

	//Backround and Texts
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	sf::Text result;
	sf::Text algor;
	sf::Text instructions;
	sf::Text instructions2;
	sf::Text instructions3;
	sf::Font font;

	//Buttons
	sf::RectangleShape startBtn;
	sf::Texture startTex;
	sf::RectangleShape endBtn;
	sf::Texture endTex;
	sf::RectangleShape wallsBtn;
	sf::Texture wallsTex;
	void collisionCheckButtons();

	//Path Finding Algorithms
	Astar astar;
	Lee lee;

	//Determine which algorithm to use
	bool algorithm = true;

	//Display Grid
	DisplayGrid displayGrid;
	int drawingMode = 1;
	
};
