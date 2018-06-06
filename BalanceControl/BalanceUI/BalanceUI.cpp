// BalanceUI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "../BalanceLib/GameController.h"
#include <iostream>


int main()
{
	// Create the main window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	const int height = 800;
	const int width = 1200;
	sf::RenderWindow window(sf::VideoMode(width, height), "Balance", sf::Style::Default, settings);

	window.setFramerateLimit(60);
	int x = 0;
	const int dx = -600;
	int y = 0;
	const int dy = -200;
	const float radius = 10;
	sf::CircleShape circle{ radius };

	//Setup Game setting
	GameController test_system{};
	test_system.controller_.set_kp(0.3);
	test_system.controller_.set_kd(2);
	test_system.controller_.set_ki(0.0);
	auto newsetpoint = test_system.update_values(1);
	auto position = 0;
	float angle = 0;

	// Start the game loop
	while (window.isOpen())
	{

		//calc the position
		
		position = test_system.ball_.get_position();
		angle = test_system.seesaw_.get_angle(0) * -1;

		newsetpoint = test_system.update_values(newsetpoint);
		std::cout << "position: " << position << " angle: " << angle << std::endl;

		x = position * cos(angle);
		y = position * sin(angle);

		x += dx;
		y += dy;


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
		

		window.draw(circle);
		// Update the window
		window.display();
	}
	return EXIT_SUCCESS;
}

