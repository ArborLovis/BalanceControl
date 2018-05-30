#pragma once
class Googly
{
public:
	Googly(float radius, float position, float velocity);

	void set_velocity(float velocity);
	float get_velocity() const;
	void set_position(float position);
	float get_position() const;

	~Googly();

private:
	//float colour_;  //for later use
	float radius_;
	float position_;
	float velocity_;
	
};

