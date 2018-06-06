// BalanceOptimizer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../BalanceLib/GameController.h"
#include <iostream>



int main()
{
	
	std::cout << "Testsystem gestartet" << std::endl;
	GameController test_system{};

	


	for(auto i=0; i<100; i++)
	{
		test_system.update_values();
		std::cout << "new values at timestamp" << std::endl;
		std::getchar();
	}

	
    return 0;
}

