#pragma once

#include "Googly.h"
#include "Physics.h"
#include "Rocker.h"
#include "Stabilizer.h"
#include <chrono>

class GameController
{
public:
	GameController();

	/**
	* @param input_angle This angle should be given in radians
	*					  and is the actual angle of the system.
	* @return The updated angle in a given time delta will be returned.
	*			The angle will be between -pi/8 and +pi/8.
	*/
	float update_values(float input_angle);
	
	float get_ball_position() const;
	float get_seesaw_angle(const long long time_delta_us);
	void set_ctr_kp(float kp);
	void set_ctr_kd(float kd);
	void set_ctr_ki(float ki);

private:
	Googly ball_;
	Physics physics_;
	Rocker seesaw_;
	Stabilizer controller_;
}; 
