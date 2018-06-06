#include "../BalanceLib/Physics.h"
#include <chrono>
#include <math.h>
#include <exception>

Physics::Physics()
	: g_{ static_cast<float>(9.81) }, act_vel_{ 0 }, act_acc_{ 0 }, act_angle_{ 0 }, 
	  time_delta_{ 0 }
{
	sys_now_dur_ = std::chrono::system_clock::now().time_since_epoch();
	act_time_ = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

float Physics::calc_velocity(float angle, float act_veloc, const long long time_delta_us)
{
	const sys_now_duration act_clk_time;
	const sys_rep_us act_time_us = std::chrono::duration_cast<std::chrono::microseconds>(act_clk_time).count();
	const long long time_delta = act_time_us - act_time_;
	
	act_time_ = act_time_us;
	act_angle_ = angle;
	time_delta_ = time_delta;

	const float PI = 3.141592;
	act_acc_ = g_ * sin(angle*PI/180.0);
	act_vel_ = act_acc_ * time_delta_us * 1e-6 + act_veloc;	// m/s
	
	return act_vel_;
}

float Physics::calc_position(const float act_pos, const float act_veloc, const long long time_delta_us)
{
	return (act_veloc * time_delta_us + act_pos);
}

