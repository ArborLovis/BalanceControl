#pragma once
#include "Math_const.h"
#include <chrono>

class Rocker
{
public:

	Rocker(float lenght = 2, float act_angle = 0);	//prev. init angle: pi/16

	float get_angle(const float delta_time_micro);
	void set_angle(float target_angle);

private:

	float length_;
	float target_angle_;
	float act_angle_;
	constexpr static float min_angle_ = -(pi / 8);
	constexpr static float max_angle_ = (pi / 8);
	constexpr static float max_ang_speed_micro_ = (pi / 4) / 1000000;  //per microsecond
	
	void angle_change(const float delta_time_micro);
};

