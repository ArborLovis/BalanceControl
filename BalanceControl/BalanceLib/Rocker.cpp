#include "Rocker.h"


Rocker::Rocker(float length, float act_angle, float min_angle, float max_angle)
{
	length_ = length;
	act_angle_ = act_angle;
	min_angle_ = min_angle;
	max_angle_ = max_angle;
}

float Rocker::get_angle() const //const = no changes from membervariables
{
	return act_angle_;
}

void Rocker::set_angle(float act_angle)
{
	act_angle_ = act_angle;
}

