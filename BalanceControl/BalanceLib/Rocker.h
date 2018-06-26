#pragma once
#include "Math_const.h"
#include <chrono>

class Rocker
{
public:

	Rocker(float lenght = 2, float act_angle = 0);	//prev. init angle: pi/16

	float get_angle(const float delta_time_micro);
	void set_angle(float target_angle);
	
	/*
	Note: VS wants a copy-assignment operator. Otherwise in line 59 in BalanceUI.cpp apper an error.
		  Line 44 is just fine with the compiler. I know this follows not the rule of 5, but after
		  implementing the cpy-assignment operator, the code works fine. 

	Update to the issue: compiler can not solve the const keyword. The compiler tries to assign line by line!
	 */
	Rocker& operator=(const Rocker& other);	

private:

	float length_;
	float target_angle_;
	float act_angle_;
	const float min_angle_ = -(pi / 8);
	const float max_angle_ = (pi / 8);
	const float max_ang_speed_micro_ = (pi / 4) / 1000000;  //per microsecond
	
	void angle_change(const float delta_time_micro);
};

