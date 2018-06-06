#include "GameController.h"




GameController::GameController()
{
}

float GameController::update_values(float input_angle)
{
	const long long time_delta_us = 100;

	float act_vel;
	float act_pos;
	float act_angle;
	float new_vel;
	float new_pos;
	float desired_angle = input_angle;

	act_vel = ball_.get_velocity();
	act_pos = ball_.get_position();

	seesaw_.set_angle(desired_angle);
	act_angle = seesaw_.get_angle(time_delta_us);

	new_vel = physics_.calc_velocity(act_angle, act_vel, time_delta_us);
	new_pos = physics_.calc_position(act_pos, act_vel, time_delta_us);

	ball_.set_position(new_pos);
	ball_.set_velocity(new_vel);
	act_pos = ball_.get_position();

	desired_angle = controller_.calc_setpoint(act_pos);


	return desired_angle;

}


