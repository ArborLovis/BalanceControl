#include "Stabilizer.h"


Stabilizer::Stabilizer(float kp, float ki, float kd, float min_angle, float max_angle, float cycletime)
{
	kp_ = kp;
	ki_ = ki;
	kd_ = kd;
	min_angle_ = min_angle;
	max_angle_ = max_angle;

	setvalue_ = 0;
	cycletime_ = cycletime;
	error_last_ = 0;

	windup_pos_ = 10000;
	windup_neg_ = -10000;
	error_sum_ = 0;
}

float Stabilizer::calc_setpoint(float position)
{
	
	auto error = setvalue_ - position;

	error_sum_ += error;
	if (error_sum_ > windup_pos_)
		error_sum_ = windup_pos_;
	else if (error_sum_ < windup_neg_)
		error_sum_ = windup_neg_;

	// calculate the individual error portions
	// proportional part
	auto error_p = error * kp_;

	// integral part
	auto error_i = error_sum_ * cycletime_ * ki_;

	// differential part
	auto error_d = (error - error_last_) * kd_ / cycletime_;
	error_last_ = error;


	// calculated setpoint (angle)
	auto y = error_p + error_i + error_d;

	// limit angle to min max
	if (y < min_angle_)
	{
		y = min_angle_;
	}
		
	else if (y > max_angle_)
	{
		y = max_angle_;
	}		

	return y;
}

void Stabilizer::set_kp(float value)
{
	kp_ = value;
}

void Stabilizer::set_ki(float value)
{
	ki_ = value;
}

void Stabilizer::set_kd(float value)
{
	kd_ = value;
}

float Stabilizer::get_kp() const
{
	return kp_;
}

float Stabilizer::get_ki() const
{
	return ki_;
}

float Stabilizer::get_kd() const
{
	return kd_;
}
