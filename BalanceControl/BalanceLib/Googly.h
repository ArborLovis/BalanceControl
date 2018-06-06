#pragma once
class Googly
{
public:
	Googly(float radius = 1, float position = 0, float velocity = 0);

	void set_velocity(float velocity);
	float get_velocity() const;
	void set_position(float position);
	float get_position() const;


private:
	//float colour_;  //for later use
	float radius_;
	float position_;
	float velocity_;
	
};

