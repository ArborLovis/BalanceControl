// BalanceOptimizer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../BalanceLib/GameController.h"
#include <iostream>
#include <array>
#include <cmath>

// simulated duration time --> 2ms
// error after 5s --> 2500 durations of update_values

void print_cli_user_notes();

int main()
{
	//setup of the system under test
	GameController test_system{};
	Stabilizer pid_control = test_system.get_copied_controller();
	Googly ball = test_system.get_copied_ball();

	auto newsetpoint = test_system.update_values(0.1);
	float act_ball_pos = ball.get_position();
	float max_ball_pos = act_ball_pos;
	float max_pos_mean_err = 0.0f;
	float max_pos_abs_err = 0.0f;
	float dist_error = 0.0f;
	float dist_abs_err = 0.0f;
	const float duration_time = 2e-3;
	std::array<float, 3> ball_pos_setpoint = { 0.0f, 0.5f, -0.5f };
	
	float old_dist_err = FLT_MAX;
	float old_dist_abs_err = FLT_MAX;

	//pid parameters
	float kp = 0.1f;
	float ki = 0.1f;
	float kd = 0.1f;
	std::array<float, 3> best_param = { 0.0f, 0.0f, 0.0f };
	std::array<float, 3> best_param_2 = { 0.0f, 0.0f, 0.0f };

	//set initial ball speed
	test_system.set_ball_velocity(0.5);
	test_system.set_rocker_angle_to_zero();
	auto duration = 0;

	print_cli_user_notes();

	for (auto h = 0; h < 1; h++)	// <- here the position of the ball can be changed; simulation with all pid param. starts again
	{
		//reset parameters for new simulation
		old_dist_err = FLT_MAX;
		old_dist_abs_err = FLT_MAX;
		kp = 0.1f;
		ki = 0.1f;
		kd = 0.1f;

		//step size: 0.1 --> max. param value: 5
		for (auto l = 0; l < 50; l++)	//modification of parameter kd
		{
			//set new kd value
			test_system.set_param_pid_ctr(kp, ki, kd);
			ki = 0.1f;
			kp = 0.1f;

			for (auto k = 0; k < 50; k++)	//modification of parameter ki
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
					dist_abs_err = 0.0f;
					max_ball_pos = 0.0f;
					test_system.set_ball_position(ball_pos_setpoint.at(h));		//test
					test_system.set_ball_velocity(-0.5);	//pushing the ball to the right
					test_system.set_rocker_angle_to_zero();

					for (auto i = 0; i < 5000; i++)		//simulation time: 10s (2ms update time controller)
					{
						//update values
						ball = test_system.get_copied_ball();
						act_ball_pos = ball.get_position();
						if (i == 2500)
							test_system.set_ball_velocity(0.5);	//push ball to the left after 5s
						
						//calculation of the deviation of the distance
						dist_error += pow(act_ball_pos,2);			//squared deviation
						dist_abs_err += abs(act_ball_pos);			//absolute deviation
						newsetpoint = test_system.update_values(newsetpoint);

						if (abs(act_ball_pos) > max_ball_pos)	//get maximum position
						{
							max_ball_pos = abs(act_ball_pos);
							if (abs(act_ball_pos) > 1.0f)		//controller parameter does not fit --> out of range --> ball fall of the seesaw
							{
								dist_error = FLT_MAX;
								dist_abs_err = FLT_MAX;
								act_ball_pos = FLT_MAX;
								break;
							}
						}

						duration++;
					}

					if ((old_dist_err > abs(dist_error)))
					{
						old_dist_err = abs(dist_error);
						max_pos_mean_err = max_ball_pos;
						best_param_2.at(0) = kp;
						best_param_2.at(1) = ki;
						best_param_2.at(2) = kd;
					}

					if ((old_dist_abs_err > dist_abs_err))
					{
						old_dist_abs_err = dist_abs_err;
						max_pos_abs_err = max_ball_pos;
						best_param.at(0) = kp;
						best_param.at(1) = ki;
						best_param.at(2) = kd;
					}
				}

				ki += 0.1f;
			}

			kd += 0.1f;
		}
	
		std::cout << "\n######## Statistic ########" << std::endl;
		std::cout << "mean error of the distance: " << old_dist_err << std::endl;
		std::cout << "max. pos reached by mean error: " << max_pos_mean_err << std::endl;
		std::cout << "abs. error of the distance: " << old_dist_abs_err << std::endl;
		std::cout << "max. pos reached by abs. error: " << max_pos_abs_err << std::endl;

		std::cout << "\nPID controller parameters: " << "KP: " << best_param.at(0) << ";\t" 
				  << "KI: " << best_param.at(1)	<< ";\t" << "KD: " << best_param.at(2) << std::endl;
		std::cout << "\nPID controller parameters: " << "KP: " << best_param_2.at(0) << ";\t"
			<< "KI: " << best_param_2.at(1) << ";\t" << "KD: " << best_param_2.at(2) << std::endl;
		std::cout << "#durations: " << duration << std::endl;
	}

	std::getchar();
    return 0;
}

void print_cli_user_notes()
{
	std::cout << "\n\t\tBRUTE FORCE OPTIMIZATION\n\n";
	std::cout << "Note: This optimization varies the controller values kp, ki and kd ";
	std::cout << "in a step size of 0.1. \nMore than 350.000.000 compinations are made!";
	std::cout << "\nBe aware that this optimization takes a while." << std::endl << std::endl;
}

