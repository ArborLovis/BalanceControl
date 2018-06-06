#pragma once
#include <chrono>
const float PI = 3.141592;

class Stabilizer
{
public:
	Stabilizer(float kp = 1, float ki = 0.05 , float kd = 0.5, float min_angle = -PI/8, float max_angle = PI/8, float cycletime = 0.01);
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

