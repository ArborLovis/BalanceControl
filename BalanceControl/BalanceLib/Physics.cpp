/**
 * Physics.cpp
 * Purpose: Calculation of velocity and distance in dependence
 *			on an angle.
 *			
 *	@author Patrick Schuster
 *	@version 1.0 09/06/18
 */

#include "../BalanceLib/Physics.h"
#include <chrono>
#include <cmath>

Physics::Physics()
	: g_{ static_cast<float>(9.81) }, act_vel_{ 0 }, act_acc_{ 0 }, low_limit_angle_{ -90 },
	  high_limit_angle_{ 90 }
{
}

float Physics::calc_velocity(float angle, float act_veloc, const long long time_delta_us)
{
	if (angle < low_limit_angle_)
		angle = low_limit_angle_;
	else if (angle > high_limit_angle_)
		angle = high_limit_angle_;

	static const float PI_ = 3.141592;
	act_acc_ = g_ * sin(angle*PI_/180.0);
	act_vel_ = act_acc_ * time_delta_us * 1e-6 + act_veloc;	// m/s
	
	return act_vel_;
}

float Physics::calc_position(const float act_pos, const float act_veloc, const long long time_delta_us)
{
	return (act_veloc * time_delta_us * 1e-6 + act_pos);
}

