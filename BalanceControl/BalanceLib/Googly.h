#pragma once

class Googly
{
public:
	Googly(float radius = 1, float position = 0, float velocity = 0.0f);	//prev. init vel.: 1.5f

	void set_velocity(float velocity);
	float get_velocity() const;
	void set_position(float position);
	float get_position() const;
	float get_radius() const;

private:
	//float colour_;  //for later use
	float radius_;
	float position_;
	float velocity_;
	
};

