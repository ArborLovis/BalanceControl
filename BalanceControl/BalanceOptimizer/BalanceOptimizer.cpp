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
	float dist_error = 0.0f;
	float dist_abs_err = 0.0f;
	const float duration_time = 2e-3;
	std::array<float, 3> ball_pos_setpoint = { 0.0f, 0.5f, -0.5f };
	
	float old_dist_err = FLT_MAX;
	float min_pos_ctr = FLT_MAX;
	float old_dist_abs_err = FLT_MAX;
	bool ignore_dist_err = false;

	//pid parameters
	float kp = 0.1f;
	float ki = 0.1f;
	float kd = 0.1f;
	std::array<float, 3> best_param_1 = { 0.0f, 0.0f, 0.0f };
	std::array<float, 3> best_param_2 = { 0.0f, 0.0f, 0.0f };
	std::array<float, 3> best_param_3 = { 0.0f, 0.0f, 0.0f };

	//set initial ball speed
	test_system.set_ball_velocity(0.5);
	test_system.set_rocker_angle_to_zero();
	auto duration = 0;

	print_cli_user_notes();

	for (auto h = 0; h < 3; h++)
	{
		min_pos_ctr = FLT_MAX;
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

						dist_error += act_ball_pos;		//calculation of the deviation of the distance
						dist_abs_err += abs(act_ball_pos);
						newsetpoint = test_system.update_values(newsetpoint);

						if (abs(act_ball_pos) > max_ball_pos)	//get maximum position
						{
							max_ball_pos = abs(act_ball_pos);
							if (abs(act_ball_pos) > 1.0f)		//controller parameter does not fit --> out of range --> ball fall of the seesaw
							{
								ignore_dist_err = true;
								break;
							}
						}

						duration++;
					}

					if ((old_dist_err > abs(dist_error)) && (ignore_dist_err == false))
					{
						old_dist_err = abs(dist_error);
						best_param_1.at(0) = kp;
						best_param_1.at(1) = ki;
						best_param_1.at(2) = kd;

						/*
						std::cout << "######## Statistic ########\n" << std::endl;
						std::cout << "KP: " << kp << "\tKI: " << ki << "\tKD: " << kd << std::endl;
						std::cout << std::endl << "max. abs. position reached: " << max_ball_pos << std::endl;
						std::cout << "error of the distance (deviation): " << dist_error << std::endl;
						std::cout << "absolute error of the distance: " << dist_abs_err << std::endl << std::endl;
						*/
					}

					if (abs(act_ball_pos) < min_pos_ctr && (ignore_dist_err == false))	//get minimum of the max reached distance
					{
						min_pos_ctr = abs(act_ball_pos);
						best_param_2.at(0) = kp;
						best_param_2.at(1) = ki;
						best_param_2.at(2) = kd;

						/*
						std::cout << "######## Statistic - 2 ########\n" << std::endl;
						std::cout << "KP: " << kp << "\tKI: " << ki << "\tKD: " << kd << std::endl;
						std::cout << std::endl << "max. position reached: " << max_ball_pos << std::endl;
						std::cout << "min. controlled position reached: " << min_pos_ctr << std::endl;
						std::cout << "error of the distance (deviation): " << dist_error << std::endl << std::endl;
						*/
					}

					if ((old_dist_abs_err > dist_abs_err) && (ignore_dist_err == false))
					{
						old_dist_abs_err = dist_abs_err;
						best_param_3.at(0) = kp;
						best_param_3.at(1) = ki;
						best_param_3.at(2) = kd;

						std::cout << "######## Statistic - 3 ########\n" << std::endl;
						std::cout << "KP: " << kp << "\tKI: " << ki << "\tKD: " << kd << std::endl;
						std::cout << std::endl << "max. abs. position reached: " << max_ball_pos << std::endl;
						std::cout << "error of the distance (deviation): " << dist_error << std::endl;
						std::cout << "absolute error of the distance: " << dist_abs_err << std::endl << std::endl;
					}

					ignore_dist_err = false;
				}

				ki += 0.1f;
			}

			kd += 0.1f;
		}
	
		std::cout << "######## Statistic ########" << std::endl;
		std::cout << "error of the distance (deviation): " << old_dist_err << std::endl;
		std::cout << "min. controlled position reached: " << min_pos_ctr << std::endl;
		std::cout << "Test param 1: " << best_param_1.at(0) << ";\t" << best_param_1.at(1) 
				  << ";\t" << best_param_1.at(2) << std::endl;
		std::cout << "Test param 2: " << best_param_2.at(0) << ";\t" << best_param_2.at(1)
			<< ";\t" << best_param_2.at(2) << std::endl;
		std::cout << "Test param 3: " << best_param_3.at(0) << ";\t" << best_param_3.at(1)
			<< ";\t" << best_param_3.at(2) << std::endl;
		std::cout << "#durations: " << duration << std::endl;
	}

	std::getchar();
    return 0;
}

void print_cli_user_notes()
{
	std::cout << "BRUTE FORCE OPTIMIZATION\n\n";
	std::cout << "Note: This optimization varies the controller values kp, ki and kd";
	std::cout << "in a step size of 0.1. More than 350.000.000 compinations are made!";
	std::cout << "Be aware that this optimization takes a while." << std::endl << std::endl;
}

