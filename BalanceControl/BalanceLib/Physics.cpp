#include "Physics.h"
#include <chrono>
#include <math.h>

Physics::Physics(float act_vel, sys_now_duration sys_act_dur)
	: g_{ static_cast<float>(9.81) }, act_vel_{act_vel}, act_acc_{ 0 }, act_angle_{ 0 }, 
	  sys_now_dur_{ sys_act_dur }
{
	act_time_ = std::chrono::duration_cast<std::chrono::microseconds>(sys_now_dur_).count();
}

bool Physics::dummy_physics() const
{
	return true;
}
