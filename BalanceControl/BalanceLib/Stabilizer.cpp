#include "Stabilizer.h"
#include <chrono>


Stabilizer::Stabilizer(float kp, float ki, float kd, float min_angle, float max_angle)
{
	kp_ = kp;
	ki_ = ki;
	kd_ = kd;
	min_angle_ = min_angle;
	max_angle_ = max_angle;

	const auto sys_time_now = std::chrono::system_clock::now().time_since_epoch();
	sys_time_old_ = std::chrono::duration_cast<std::chrono::microseconds>(sys_time_now).count();

}

float Stabilizer::calc_setpoint(float position)
{
	return 0.0f;
}

void Stabilizer::set_kp(float value)
{
}

void Stabilizer::set_ki(float value)
{
}

void Stabilizer::set_kd(float value)
{
}

float Stabilizer::get_kp()
{
	return 0.0f;
}

float Stabilizer::get_ki()
{
	return 0.0f;
}

float Stabilizer::get_kd()
{
	return 0.0f;
}
