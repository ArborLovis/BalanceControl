#pragma once
#include <chrono>

class Stabilizer
{
public:
	Stabilizer(float kp, float ki, float kd, float min_angle, float max_angle, float cycletime);
	float calc_setpoint(float position);

	void set_kp(float value);
	void set_ki(float value);
	void set_kd(float value);

	float get_kp() const;
	float get_ki() const;
	float get_kd() const;


private:
	float cycletime_;

	float kp_;
	float ki_;
	float kd_;


	float error_sum_;
	float max_angle_;
	float min_angle_;

	float setvalue_;
	float error_last_;

	float windup_pos_;
	float windup_neg_;

};

