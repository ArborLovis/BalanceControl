// BalanceOptimizer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../BalanceLib/GameController.h"
#include <iostream>
#include <array>

// simulated duration time --> 5ms
// error after 5s --> 1000 durations of update_values

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
	float old_ball_pos_max = act_ball_pos;
	float old_ball_pos_min = act_ball_pos;
	float dist_error = 0.0f;
	const float duration_time = 5e-3;
	
	float old_dist_err = FLT_MAX;
	float old_old_pos_max = FLT_MAX;
	bool ignore_dist_err = false;

	//pid parameters
	float kp = 0.1f;
	float ki = 0.1f;
	float kd = 0.1f;

	//set initial ball speed
	test_system.set_ball_velocity(0.5);
	auto duration = 0;

	//step size: 0.1 --> max. param value: 5
	for(auto l = 0; l < 50; l++)	//modification of parameter kd
	{ 
		//set new kd value
		test_system.set_param_pid_ctr(kp, ki, kd);
		ki = 0.1f;
		kp = 0.1f;

		for(auto k = 0; k < 50; k++)	//modification of parameter ki
		{ 
			//set new ki value
			test_system.set_param_pid_ctr(kp, ki, kd);
			kp = 0.1f;

			for (auto j = 0; j < 50; j++)	//modification of parameter kp
			{
				test_system.set_param_pid_ctr(kp, ki, kd);
				kp += 0.1f;

				//reset system and statistic
				dist_error = 0.0f;
				old_ball_pos_max = 0.0f;
				old_ball_pos_min = 0.0f;
				test_system.set_ball_position(0);
				test_system.set_ball_velocity(0.5);
				test_system.set_rocker_angle(0);

				for (auto i = 0; i < 1000; i++)
				{
					//update values
					ball = test_system.get_copied_ball();
					seesaw = test_system.get_copied_seesaw();
					act_ball_pos = ball.get_position();
					
					dist_error += act_ball_pos * duration_time;	//calculation of the deviation of the distance
					newsetpoint = test_system.update_values(newsetpoint);

					if (act_ball_pos > old_ball_pos_max)	//get maximum position
					{
						old_ball_pos_max = act_ball_pos;
						if (act_ball_pos > 1.0f)		//controller parameter does not fit --> out of range --> ball fall of the seesaw
						{
							ignore_dist_err = true;
							break;
						}
					}		
					else if(act_ball_pos < old_ball_pos_min)
					{
						old_ball_pos_min = act_ball_pos;
						if(act_ball_pos < -1.0)
						{
							ignore_dist_err = true;
							break;
						}
						
					}

					duration++;
				}

				if ((old_dist_err > dist_error) && (ignore_dist_err == false) && (dist_error > 0))
				{
					old_dist_err = dist_error;

					std::cout << "######## Statistic ########\n" << std::endl;
					std::cout << "KP: " << kp << "\tKI: " << ki << "\tKD: " << kd << std::endl;
					std::cout << std::endl << "max. position reached: " << old_ball_pos_max << std::endl;
					std::cout << "min. position reached: " << old_ball_pos_min << std::endl;
					std::cout << "error of the distance (deviation): " << dist_error << std::endl << std::endl;
				}
				
				if(old_ball_pos_max < old_old_pos_max && (ignore_dist_err == false))	//get minimum of the max reached distance
				{
					old_old_pos_max = old_ball_pos_max;

					std::cout << "######## Statistic - 2 ########\n" << std::endl;
					std::cout << "KP: " << kp << "\tKI: " << ki << "\tKD: " << kd << std::endl;
					std::cout << std::endl << "max. position reached: " << old_ball_pos_max << std::endl;
					std::cout << "min. position reached: " << old_ball_pos_min << std::endl;
					std::cout << "error of the distance (deviation): " << dist_error << std::endl << std::endl;
				}
				
				ignore_dist_err = false;
			}

			ki += 0.1f;
		}

		kd += 0.1f;
	}
		
	std::cout << "######## Statistic ########" << std::endl;
	std::cout << std::endl << "max. position reached: " << old_ball_pos_max << std::endl;
	std::cout << "error of the distance (deviation): " << old_dist_err << std::endl << std::endl;
	std::cout << "#durations: " << duration << std::endl;

	std::getchar();
    return 0;
}

