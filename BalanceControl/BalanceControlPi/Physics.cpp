#include "Physics.h"

Physics::Physics(float act_vel, system_clk sys_act_time)
	: g_{ 9.81 }, act_vel_{act_vel}, act_acc_{ 0 }, act_angle_{ 0 }, 
	  sys_now_{ sys_act_time }, act_time_{ std::chrono::duration_cast<std::chrono::microseconds>(sys_act_time.now().time_since_epoch()).count()}
{
}
