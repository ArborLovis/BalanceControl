// BalanceUI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <SFML/Graphics.hpp>


int main()
{
	// Create the main window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	const int height = 400;
	const int width = 600;
	sf::RenderWindow window(sf::VideoMode(width, height), "Balance", sf::Style::Default, settings);

	window.setFramerateLimit(60);
	int x = -200;
	int dx = -3;
	const int y = -100;
	const float radius = 10;
	sf::CircleShape circle{ radius };

	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// Clear screen
		window.clear();
		// Draw the string
		
		circle.setOrigin(x, y);
		if(x > 0 || x < -(width - 2*radius))
		{
			dx = -dx;
		}
		x += dx;

		window.draw(circle);
		// Update the window
		window.display();
	}
	return EXIT_SUCCESS;
}

