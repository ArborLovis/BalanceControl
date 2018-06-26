#include "Rocker.h"

Rocker::Rocker(float length, float act_angle)
{
	length_ = length;
	act_angle_ = act_angle;
	target_angle_ = 0;
}

float Rocker::get_angle(const float delta_time_micro) //const = no changes from membervariables
{
	auto const hysteresis = 0.001745329;	// 0.1� toleranz
	if(!((act_angle_ >= target_angle_-hysteresis) && (act_angle_ <= target_angle_ + hysteresis)))
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

Rocker & Rocker::operator=(const Rocker & other)
{
	length_ = other.length_;
	target_angle_ = other.target_angle_;
	act_angle_ = other.act_angle_;

	return *this;
}

void Rocker::angle_change(const float delta_time_micro)
{
	const float angle_change = (max_ang_speed_micro_ * delta_time_micro);

	if (act_angle_ > target_angle_)
		act_angle_ -= angle_change;
	else if (act_angle_ < target_angle_)
		act_angle_ += angle_change;
	else
		act_angle_ += 0;
}
