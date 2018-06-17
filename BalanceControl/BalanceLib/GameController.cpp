#include "GameController.h"
#include "Rocker.h"
#include <iostream>


GameController::GameController() = default;

float GameController::update_values(float input_angle)	
{
	const long long time_delta_us = 5000;

	const float act_vel = ball_.get_velocity();
	float act_pos = ball_.get_position();

	seesaw_.set_angle(input_angle);
	const float act_angle = seesaw_.get_angle(time_delta_us);

	const float new_vel = physics_.calc_velocity(act_angle*180.0f/pi, act_vel, time_delta_us);
	const float new_pos = physics_.calc_position(act_pos, act_vel, time_delta_us);

	//std::cout << "\n\nDebug velocity: " << new_vel << std::endl;
	//std::cout << "\n\nDebug position PHY: " << new_pos << std::endl;

	ball_.set_position(new_pos);
	ball_.set_velocity(new_vel);
	act_pos = ball_.get_position();

	//std::cout << "\n\nDebug position Ball: " << act_pos << std::endl;

	input_angle = controller_.calc_setpoint(act_pos);

	return input_angle;

}

//float GameController::get_ball_position() const
//{
//	return ball_.get_position();
//}
//
//float GameController::get_seesaw_angle(const long long time_delta_us)
//{
//	return seesaw_.get_angle(static_cast<float>(time_delta_us));
//}
//
//void GameController::set_ctr_kp(float kp)
//{
//	controller_.set_kp(kp);
//}
//
//void GameController::set_ctr_kd(float kd)
//{
//	controller_.set_kd(kd);
//}
//
//void GameController::set_ctr_ki(float ki)
//{
//	controller_.set_ki(ki);
//}

Googly GameController::get_copied_ball() const
{
	return ball_;
}

Rocker GameController::get_copied_seesaw() const
{
	return seesaw_;
}

Physics GameController::get_copied_phy_obj() const
{
	return physics_;
}

Stabilizer GameController::get_copied_controller() const
{
	return controller_;
}

void GameController::set_param_pid_ctr(const float kp, const float ki, const float kd)
{
	controller_.set_kp(kp);
	controller_.set_kd(kd);
	controller_.set_ki(ki);
}


