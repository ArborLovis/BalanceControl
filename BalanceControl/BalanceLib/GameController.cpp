#include "GameController.h"




GameController::GameController()
{
}

/**
 * @param input_angle This angle should be given in radians
 *					  and is the actual angle of the system.
 * @returns The updated angle in a given time delta will be returned.
 *			The angle will be between -pi/8 and +pi/8.
 */
float GameController::update_values(float input_angle)	
{
	const long long time_delta_us = 2000;//16667; //60Hz

	const float act_vel = ball_.get_velocity();
	float act_pos = ball_.get_position();

	seesaw_.set_angle(input_angle);
	const float act_angle = seesaw_.get_angle(time_delta_us);

	const float new_vel = physics_.calc_velocity(act_angle*180.0f/pi, act_vel, time_delta_us);
	const float new_pos = physics_.calc_position(act_pos, act_vel, time_delta_us);

	ball_.set_position(new_pos);
	ball_.set_velocity(new_vel);
	act_pos = ball_.get_position();

	input_angle = controller_.calc_setpoint(act_pos);

	return input_angle;

}


