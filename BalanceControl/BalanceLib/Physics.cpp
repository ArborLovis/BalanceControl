#include "../BalanceLib/Physics.h"
#include <chrono>
#include <math.h>
#include <exception>

Physics::Physics(float act_vel, sys_now_duration sys_act_dur)
	: g_{ static_cast<float>(9.81) }, act_vel_{act_vel}, act_acc_{ 0 }, act_angle_{ 0 }, 
	  sys_now_dur_{ sys_act_dur }, 
	  act_time_{ std::chrono::duration_cast<std::chrono::microseconds>(sys_now_dur_).count() },
	  time_delta_{act_time_}
{
	//act_time_ = std::chrono::duration_cast<std::chrono::microseconds>(sys_now_dur_).count();
}

float Physics::calc_velocity(float angle, float act_veloc, long long act_time_us)
{
	const long long time_delta = act_time_us - act_time_;
	act_time_ = act_time_us;
	act_angle_ = angle;
	time_delta_ = time_delta;

	if((act_veloc >= act_vel_ + 0.5) || (act_veloc <= act_vel_ + 0.5) || (act_vel_ == act_veloc))
	{
		const float PI = 3.141592;
		act_acc_ = g_ * sin(angle*PI/180.0);
		act_vel_ = act_acc_ * time_delta * 1e-6 + act_veloc;	// m/s
	}
	else
	{
		throw std::exception("velocity is not consecrated");
	}
	return act_vel_;
}

float Physics::calc_position(const float act_pos, const float act_veloc)
{
	const sys_now_duration sys_clk_now;
	const sys_rep_us time_us_now = std::chrono::duration_cast<std::chrono::microseconds>(sys_clk_now).count();
	static sys_rep_us act_time_pos = act_time_;
	static sys_rep_us time_delta_pos = time_us_now - act_time_pos;
	act_time_pos = time_us_now;
	
	return (act_veloc * time_delta_pos + act_pos);
}

bool Physics::dummy_physics() const
{
	return true;
}
