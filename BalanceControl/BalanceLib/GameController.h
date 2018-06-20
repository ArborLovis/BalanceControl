#pragma once

#include "Googly.h"
#include "Physics.h"
#include "Rocker.h"
#include "Stabilizer.h"
#include <chrono>

class GameController
{
public:
	GameController();

	/**
	* @param input_angle This angle should be given in radians
	*					  and is the actual angle of the system.
	* @return The updated angle in a given time delta will be returned.
	*			The angle will be between -pi/8 and +pi/8.
	*/
	float update_values(float input_angle);

	Googly get_copied_ball() const;
	void set_ball_velocity(const float vel);
	void set_ball_position(const float pos);	//needed for reseting postion in GameOptimizer


	Rocker get_copied_seesaw() const;
	void set_rocker_angle_to_zero();
	Physics get_copied_phy_obj() const;

	Stabilizer get_copied_controller() const;
	void set_param_pid_ctr(const float kp, const float ki, const float kd);

private:
	Googly ball_;
	Physics physics_;
	Rocker seesaw_;
	Stabilizer controller_;
}; 
