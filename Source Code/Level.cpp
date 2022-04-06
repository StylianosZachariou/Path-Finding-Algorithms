#include "Level.h"
#include <iostream>
#include <Windows.h>

using namespace std;

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	//Grid Initialization
	grid.width = 100;
	grid.height = 100;

	//Background
	backgroundTexture.loadFromFile("gfx/Background.jpg");
	background.setTexture(&backgroundTexture);
	background.setPosition(0, 0);
	background.setSize(sf::Vector2f(2000, 1900));

	//Display
	grid.updateGrid(grid.height,grid.width);
	displayGrid.setGridPositions(grid.height, grid.width, grid);

	//Text
	font.loadFromFile("font/font.ttf");
	result.setFont(font);
	result.setCharacterSize(100);
	result.setFillColor(sf::Color::Black);
	result.setPosition(50,175);

	algor.setFont(font);
	algor.setCharacterSize(150);
	algor.setFillColor(sf::Color::Black);
	algor.setPosition(50,0);
	algor.setString("Algorithm: A*");

	instructions.setFont(font);
	instructions.setCharacterSize(75);
	instructions.setFillColor(sf::Color::Black);
	instructions.setPosition(50, 1800);
	instructions.setString("Columns: Increase:E-Decrease:D          Rows: Increase:W-Decrease:S");

	instructions2.setFont(font);
	instructions2.setCharacterSize(75);
	instructions2.setFillColor(sf::Color::Black);
	instructions2.setPosition(1650, 10);
	instructions2.setString("Start: Space");

	instructions3.setFont(font);
	instructions3.setCharacterSize(75);
	instructions3.setFillColor(sf::Color::Black);
	instructions3.setPosition(1500, 80);
	instructions3.setString("Random Walls: R");

	//Buttons
	startTex.loadFromFile("gfx/Start.png");
	endTex.loadFromFile("gfx/End.png");
	wallsTex.loadFromFile("gfx/Walls.png");

	startBtn.setTexture(&startTex);
	startBtn.setSize(sf::Vector2f(355, 150));
	startBtn.setPosition(155.8, 1650);

	endBtn.setTexture(&endTex);
	endBtn.setSize(sf::Vector2f(355, 150));
	endBtn.setPosition(822.4, 1650);

	wallsBtn.setTexture(&wallsTex);
	wallsBtn.setSize(sf::Vector2f(355, 150));
	wallsBtn.setPosition(1489, 1650);
}

// Handle user input
void Level::handleInput()
{
	if (input->isKeyDown(sf::Keyboard::W)) //If W is pressed
	{
		input->setKeyUp(sf::Keyboard::W);
		if (grid.height < 1000) //If grid height is less than 1000
		{
			grid.height++; //Increment it by 1
			displayGrid.setGridPositions(grid.height, grid.width, grid); //Update Grid & Display
		}
	}

	if (input->isKeyDown(sf::Keyboard::S)) //If S is pressed
	{
		input->setKeyUp(sf::Keyboard::S);
		if (grid.height > 2) //If grid height is more than 2
		{
			grid.height--; //Decrement height by 1
			displayGrid.setGridPositions(grid.height, grid.width, grid); //Update Grid & Display
		}
	}

	if (input->isKeyDown(sf::Keyboard::E)) //If E is pressed
	{
		input->setKeyUp(sf::Keyboard::E);
		if (grid.width < 1000) //If grid width is less than 1000
		{
			grid.width++; //Increment increase by 1
			displayGrid.setGridPositions(grid.height, grid.width, grid); //Update Grid & Display
		}
	}

	if (input->isKeyDown(sf::Keyboard::D)) //If D is pressed
	{
		input->setKeyUp(sf::Keyboard::D);
		if (grid.width > 2) //If grid width is more than 2 
		{
			grid.width--; //Decrement width by 1
			displayGrid.setGridPositions(grid.height, grid.width, grid); //Update Grid & Display
		}
	}

	if (input->isKeyDown(sf::Keyboard::R)) //If R is pressed
	{
		input->setKeyUp(sf::Keyboard::R);
		grid.randomWalls(); //Fill grid with random walls
		displayGrid.displayEverything(grid); //display
	}

	if (input->isMouseLDown()) //If Mouse Left is left
	{
		input->setMouseLDown(false);
		collisionCheckButtons(); //Check Buttons for collisions
		displayGrid.collisionCheck({ input->getMouseX(), input->getMouseY() }, grid,drawingMode); //Check Grid for collisions
	}

	if (input->isKeyDown(sf::Keyboard::C)) //If C is pressed
	{
		displayGrid.resetDislpay(); //Reset Display
		grid.resetGrid(); //Reset Grid
	}

	if (input->isKeyDown(sf::Keyboard::Space)) //If Space is pressed
	{
		input->setKeyUp(sf::Keyboard::Space);
		if ((grid.start.x != -1) && (grid.end.x != -1)) //Start and End are on the grid
		{

			if (algorithm)  //A* ALGORITHM
			{

				if (astar.findPath(grid)) //Perform A* and check if a path is found
				{
					result.setString("Path Found!");
				}
				else
				{
					result.setString("No Path Available.");
				}

			}
			else //LEE ALGORITHM
			{
				if (lee.findPath(grid)) //Perform Lee and check if a path is found
				{
					result.setString("Path Found!");
				}
				else
				{
					result.setString("No Path Available.");
				}
			}
		}

		displayGrid.displayEverything(grid); //Display Grid
		grid.resetGrid(); //Reset Grid
	}

	if (input->isKeyDown(sf::Keyboard::A)) //If A is pressed
	{
		input->setKeyUp(sf::Keyboard::A);
		algorithm = !algorithm; //change algorithm
		
		if (algorithm)//iF algorithm is true the A*
		{
			algor.setString("Algorithm: A*");
		}
		else //Else Lee
		{
			algor.setString("Algorithm: Lee");

		}
	}
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(background);
	displayGrid.render(window);
	window->draw(result);
	window->draw(algor);
	window->draw(startBtn);
	window->draw(endBtn);
	window->draw(wallsBtn);
	window->draw(instructions);
	window->draw(instructions2);
	window->draw(instructions3);
	endDraw();
}

// Begins rendering to the back buffer
void Level::beginDraw()
{
	window->clear(sf::Color::White);
}

// Ends rendering to the back buffer.
void Level::endDraw()
{
	window->display();
}
//Check for Collisions between the mouse and the buttons
void Level::collisionCheckButtons()
{

	if (Collisions::pointToAABB({ startBtn.getPosition().x + startBtn.getSize().x,startBtn.getPosition().y + startBtn.getSize().y }, { startBtn.getPosition().x,startBtn.getPosition().y }, { input->getMouseX(),input->getMouseY() }))
	{
		drawingMode = 1;
	}

	if (Collisions::pointToAABB({ endBtn.getPosition().x + endBtn.getSize().x,endBtn.getPosition().y + endBtn.getSize().y }, { endBtn.getPosition().x,endBtn.getPosition().y }, { input->getMouseX(),input->getMouseY() }))
	{
		drawingMode = 2;
	}

	if (Collisions::pointToAABB({ wallsBtn.getPosition().x + wallsBtn.getSize().x,wallsBtn.getPosition().y + wallsBtn.getSize().y }, { wallsBtn.getPosition().x,wallsBtn.getPosition().y }, { input->getMouseX(),input->getMouseY() }))
	{
		drawingMode = 3;
	}

}


