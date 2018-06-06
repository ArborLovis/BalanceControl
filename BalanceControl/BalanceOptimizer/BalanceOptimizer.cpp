// BalanceOptimizer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../BalanceLib/GameController.h"
#include <iostream>



int main()
{
	
	std::cout << "Set value to -0.1" << std::endl;
	GameController test_system{};
	test_system.controller_.set_kp(0.01);
	auto newsetpoint = test_system.update_values(0.1);

	for(auto i=0; i<1000; i++)
	{

		std::cout << "values at " << i << ": Ball position = " << test_system.ball_.get_position() << "; angle =  " << test_system.seesaw_.get_angle(0);	
		newsetpoint = test_system.update_values(newsetpoint);
		std::cout << "; set angle to control: " << newsetpoint << std::endl;
		std::getchar();
	}

	
    return 0;
}

