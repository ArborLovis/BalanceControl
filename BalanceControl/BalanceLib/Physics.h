#pragma once
#include <chrono>

using sys_now_duration = std::chrono::duration<long long, std::ratio<1, 1000000000>>;//std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::nanoseconds>::duration;
using sys_rep_us = std::chrono::microseconds::rep;

class Physics
{
public:
	Physics(float act_vel, sys_now_duration sys_act_dur);

	float calc_velocity(float angle, float act_veloc, long long act_time_us);
	float calc_position(float act_pos, float act_veloc);

	bool dummy_physics() const;

private:
	const float g_;
	float act_vel_;
	float act_acc_;
	float act_angle_;
	sys_now_duration sys_now_dur_;
	sys_rep_us act_time_;
	sys_rep_us time_delta_;
	
};











//using sys_clk_now = std::chrono::time_point<std::chrono::system_clock>;
//using sys_duration = std::chrono::duration<long long, std::ratio<1, 1000000000>>::rep;

//std::chrono::time_point<std::chrono::system_clock> test_time = std::chrono::system_clock::now();

//auto sys_now = test_time.time_since_epoch();// .time_since_epoch();
//auto act_time = std::chrono::duration_cast<std::chrono::milliseconds>(test_time.time_since_epoch()).count();

// get actual time typedef std::chrono::nanoseconds
//sys_now_duration sys_now = std::chrono::system_clock::now().time_since_epoch();
//sys_rep_us act_time = std::chrono::duration_cast<std::chrono::microseconds>(sys_now).count();