#include "Rocker.h"


Rocker::Rocker(float length, float act_angle)
{
	length_ = length;
	act_angle_ = act_angle;
}

float Rocker::get_angle(const float delta_time_micro) //const = no changes from membervariables
{
	angle_change(delta_time_micro);

	return act_angle_;
}

void Rocker::set_angle(float target_angle)
{
	if (target_angle > max_angle_)
		target_angle_ = max_angle_;
	else if (target_angle < min_angle_)
		target_angle_ = min_angle_;
	else
		target_angle_ = target_angle;
}

void Rocker::angle_change(const float delta_time_micro)
{
	float angle_change = (max_ang_speed_micro_ * delta_time_micro);

	if (act_angle_ > target_angle_)
		act_angle_ -= angle_change;
	else if (act_angle_ < target_angle_)
		act_angle_ += angle_change;
	else
		act_angle_ += 0;
}
