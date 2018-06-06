#pragma once
const float PI = 3.141592;

class Rocker
{
public:

	Rocker(float lenght = 2, float act_angle = 0, float min_angle = -PI/8, float max_angle = PI/8);

	float get_angle() const;
	void set_angle(float act_angle);


private:

	float length_;
	float act_angle_;
	float min_angle_;
	float max_angle_;
	float max_ang_speed_;

};

