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

	window.setFramerateLimit(100);
	int x = 0;
	const int dx = -600;
	int y = 0;
	const int dy = -200;
	const float radius = 10;
	const sf::Vector2f rect_dim{ 500.0f, 5.0f };
	const sf::Color rect_color(178, 255, 102);
	sf::CircleShape circle{ radius };
	sf::RectangleShape rect{rect_dim};

	rect.setPosition(-dx,-(dy-2*radius));
	rect.setOrigin(250.0f,2.5f);
	rect.setFillColor(rect_color);

	//Setup Game setting
	GameController test_system{};
	test_system.set_ctr_kp(0.2);	//0.3
	test_system.set_ctr_kd(0.1);		//2
	test_system.set_ctr_ki(0.5);	//0.0
	float angle = 10*pi/180.0f;
	auto newsetpoint = test_system.update_values(angle);
	auto position = 0.0f;
	auto t_delta_us = 0.0f;

	// Start the game loop
	while (window.isOpen())
	{
		//calc the position	
		position = test_system.get_ball_position();
		angle = test_system.get_seesaw_angle(t_delta_us) * -1;
		
		newsetpoint = test_system.update_values(newsetpoint);
		std::cout << "position: " << position << " angle: " << angle 
				  << " new setpoint: " << newsetpoint << std::endl;

		x = static_cast<int>(position * cos(angle) * rect_dim.x / 2.0f);
		y = static_cast<int>(position * sin(angle) *rect_dim.x / 2.0f);

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
		rect.setRotation(angle * 180.0f / pi);
		//rect.rotate(angle);

		window.draw(circle);
		window.draw(rect);
		// Update the window
		window.display();
	}
	return EXIT_SUCCESS;
}

