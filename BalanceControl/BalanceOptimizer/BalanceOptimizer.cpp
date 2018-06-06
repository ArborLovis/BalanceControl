// BalanceOptimizer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../BalanceLib/GameController.h"
#include <iostream>



int main()
{
	
	std::cout << "Testsystem gestartet" << std::endl;
	GameController test_system{};
	auto test = test_system.update_values(15);


	for(auto i=0; i<100; i++)
	{
		test = test_system.update_values(test);
		
		
		std::cout << "new values at timestamp" << i << " : " << test_system.ball_.get_position() << " - " << test_system.seesaw_.get_angle(1000) << std::endl;
		std::getchar();
	}

	
    return 0;
}

