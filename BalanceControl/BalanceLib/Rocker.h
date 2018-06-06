#pragma once

#include <chrono>

class Rocker
{
	using time_type = std::chrono::time_point<std::chrono::system_clock>;

public:

	Rocker(float lenght, float act_angle);

	float get_angle(const float delta_time_mico);
	void set_angle(float act_angle);
	
private:

	const float PI = 3.141592;

	float length_;
	float target_angle_;
	float act_angle_;
	float min_angle_ = -(PI / 8);
	float max_angle_ = (PI / 8);
	const float max_ang_speed_micro_ = (PI / 4) / 1000000;  //per microsecond
	
	void angle_change(const float delta_time_micro);
};

