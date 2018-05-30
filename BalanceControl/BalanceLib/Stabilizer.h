#pragma once
#include "../../../../../../../Program Files (x86)/Microsoft Visual Studio/2017/Enterprise/VC/Tools/MSVC/14.13.26128/include/ctime"

class Stabilizer
{
public:
	Stabilizer(float kp, float ki, float kd, float min_angle, float max_angle);
	float calc_setpoint(float position);

	void set_kp(float value);
	void set_ki(float value);
	void set_kd(float value);

	float get_kp();
	float get_ki();
	float get_kd();


private:
	float kp_;
	float ki_;
	float kd_;

	auto delta_t;

	float error_sum_;
	float max_angle_;
	float min_angle_;


};

