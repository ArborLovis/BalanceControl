// BalanceOptimizer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../BalanceLib/GameController.h"
#include <iostream>



int main()
{
	std::cout << "Set value to -0.1" << std::endl;
	GameController test_system{};
	test_system.set_param_pid_ctr(0.1, 5, 0.2);
	Stabilizer pid_control = test_system.get_copied_controller();
	Googly ball = test_system.get_copied_ball();
	Rocker seesaw = test_system.get_copied_seesaw();

	auto newsetpoint = test_system.update_values(0.1);
	float act_ball_pos = ball.get_position();
	float old_ball_pos = act_ball_pos;

	for(auto i=0; i<1000; i++)
	{
		//update values
		ball = test_system.get_copied_ball();
		seesaw = test_system.get_copied_seesaw();
		act_ball_pos = ball.get_position();

		if(act_ball_pos > old_ball_pos)
		{
			old_ball_pos = act_ball_pos;
		}

		//std::cout << "values at duration nr.: " << i << ";\t Ball position = " << ball.get_position() << ";\t angle =  ";
		//std::cout << seesaw.get_angle(0) << ";" << std::endl;
		newsetpoint = test_system.update_values(newsetpoint);
		//std::cout << "set angle to control: " << newsetpoint << std::endl;
	}
		
	std::cout << std::endl << "max. position reached: " << old_ball_pos << std::endl;
	std::getchar();
    return 0;
}

