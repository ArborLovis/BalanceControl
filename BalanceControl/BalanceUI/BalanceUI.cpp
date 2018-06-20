// BalanceUI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "../BalanceLib/GameController.h"
#include <iostream>
#include <array>

void manage_ball_shape(sf::CircleShape& ball, const float radius, const std::array<sf::Uint8, 3> color_code);
void manage_seesaw_shape(sf::RectangleShape& seesaw, const int x, const int y,
						 const float length, const float witdh, const std::array<sf::Uint8, 3> color_code);
void manage_seesaw_mount(sf::ConvexShape& mount, const int x, const int y, 
						 const std::array<std::array<float, 2>, 3> points, const std::array<sf::Uint8, 3> color_code);

int main()
{
	// Create the main window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	const int height = 800;
	const int width = 1200;
	sf::RenderWindow window(sf::VideoMode(width, height), "Balance", sf::Style::Default, settings);

	//define centre and design shapes of the model
	window.setFramerateLimit(100);
	int x = 0;
	const int dx = -600;
	int y = 0;
	const int dy = -200;
	const float radius = 10.0f;
	
	sf::CircleShape circle;
	manage_ball_shape(circle, radius, { 255, 102, 102 });
	sf::RectangleShape rect;
	manage_seesaw_shape(rect, dx, dy-2*radius, 500.0f, 5.0f, { 178, 255, 102 });
	sf::ConvexShape triangle;
	const std::array<std::array<float, 2>, 3> tri_dots = { {{0.0f, 0.0f}, {-30.0f, 50.0f}, {30.0f, 50.0f}} };
	manage_seesaw_mount(triangle, dx, dy-2*radius-2.5f, tri_dots, { 0, 153, 76 });

	//Setup Game setting
	GameController test_system{};
	Googly ball = test_system.get_copied_ball();
	Rocker seesaw = test_system.get_copied_seesaw();
		
	test_system.set_param_pid_ctr(1.3f, 0.1f, 1.2f);
	//test_system.set_param_pid_ctr(0.01, 0.01, 0.01);	//for disabling the controller
	Stabilizer pid_control = test_system.get_copied_controller();

	float angle = 10*pi/180.0f;
	auto newsetpoint = test_system.update_values(angle);
	auto position = 0.0f;

	// Start the game loop
	while (window.isOpen())
	{
		//update copied opjects
		ball = test_system.get_copied_ball();
		seesaw = test_system.get_copied_seesaw();

		//calc the position	
		position = ball.get_position();
		angle = -seesaw.get_angle(0);
		
		newsetpoint = test_system.update_values(newsetpoint);
		std::cout << "position: " << position << " angle: " << angle 
				  << " new setpoint: " << newsetpoint << " velocity: " << ball.get_velocity() << std::endl;

		x = static_cast<int>(position * cos(angle) * 250.0f + radius);
		y = static_cast<int>(position * sin(angle) * 250.0f);

		x += dx;
		y += dy;

		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Q)
				{
					test_system.set_ball_velocity(0.5);	//pushing ball to the left
				}
				else if (event.key.code == sf::Keyboard::W)
				{
					test_system.set_ball_velocity(-0.5);	///pushing ball to the right
				}
				else if (event.key.code == sf::Keyboard::X)
				{
					window.close();		//close application
				}
				break;
			
			default:
				std::cout << "default event" << std::endl;
				break;
			}
		}

		// Clear screen
		window.clear();
		// Draw the string
		
		circle.setOrigin(x, y);
		rect.setRotation(angle * 180.0f / pi);

		// Update the window
		window.draw(circle);
		window.draw(rect);
		window.draw(triangle);
		window.display();
	}
	return EXIT_SUCCESS;
}

void manage_ball_shape(sf::CircleShape& ball, const float radius, const std::array<sf::Uint8, 3> color_code)
{
	const sf::Color ball_color(color_code.at(0), color_code.at(1), color_code.at(2));
	
	ball.setRadius(radius);
	ball.setFillColor(ball_color);
}

void manage_seesaw_shape(sf::RectangleShape& seesaw, const int x, const int y, 
						 const float length, const float witdh, const std::array<sf::Uint8, 3> color_code)
{
	const sf::Vector2f rect_dim{ length, witdh };
	const sf::Color rect_color(color_code.at(0), color_code.at(1), color_code.at(2));
	seesaw.setSize(rect_dim);

	seesaw.setPosition(-x, -(y - rect_dim.y / 2.0f));
	seesaw.setOrigin(rect_dim.x / 2.0f, rect_dim.y / 2.0f);
	seesaw.setFillColor(rect_color);
}

void manage_seesaw_mount(sf::ConvexShape& mount, const int x, const int y, 
						 const std::array<std::array<float, 2>, 3> points, const std::array<sf::Uint8, 3> color_code)
{
	std::cout << points.at(0).at(0) << std::endl;
	std::cout << points.at(0).at(1) << std::endl;
	std::cout << points.at(1).at(0) << std::endl;
	std::cout << points.at(1).at(1) << std::endl;

	const sf::Vector2f tri_p0{ points.at(0).at(0) , points.at(0).at(1) };
	const sf::Vector2f tri_p1{ points.at(1).at(0) , points.at(1).at(1) };
	const sf::Vector2f tri_p2{ points.at(2).at(0) , points.at(2).at(1) };

	const sf::Color mount_color{ color_code.at(0), color_code.at(1), color_code.at(2) };
	mount.setFillColor(mount_color);

	mount.setPointCount(3);
	mount.setPoint(0, tri_p0);
	mount.setPoint(1, tri_p1);
	mount.setPoint(2, tri_p2);

	mount.setOrigin(x, y);
}