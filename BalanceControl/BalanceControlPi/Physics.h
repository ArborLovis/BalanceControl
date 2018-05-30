#pragma once
#include <chrono>
#include <math.h>

using system_clk = std::chrono::system_clock;
using sys_duration = std::chrono::duration<long long, std::ratio<1, 1000000000>>::rep;

auto sys_now = system_clk::now().time_since_epoch();
auto act_time = std::chrono::duration_cast<std::chrono::microseconds>(sys_now).count();

class Physics
{
public:
	Physics(float act_vel, system_clk act_time);

private:
	const float g_;
	float act_vel_;
	float act_acc_;
	float act_angle_;
	system_clk sys_now_;
	sys_duration act_time_;
	
};