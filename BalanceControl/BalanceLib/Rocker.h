#pragma once
class Rocker
{
public:

	Rocker(float lenght, float act_angle, float min_angle, float max_angle);

	float get_angle() const;
	void set_angle(float act_angle);

	~Rocker();

private:

	float length_;
	float act_angle_;
	float min_angle_;
	float max_angle_;
	float max_ang_speed_;

};

