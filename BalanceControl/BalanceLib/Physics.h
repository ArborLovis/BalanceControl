/**
* Physics.h
* Purpose: Calculation of velocity and distance in dependence
*		   on an angle.
*
*	@author Patrick Schuster
*	@version 1.0 09/06/18
*/

#pragma once
#include <chrono>

/*Not relevant anymore
using sys_now_duration = std::chrono::duration<long long, std::ratio<1, 1000000000>>;
using sys_rep_us = std::chrono::microseconds::rep;
*/

class Physics
{
public:
	/**
	 *	Default - constructor of the class Physics. 
	 *	No other constructor available.
	 */
	Physics();

	/**
	*	Calculation of the velocity depending on the angle
	*	and starting velocity in a given time period.
	*	@param angle The angle of the surface, where the object is situated on it.
	*	@param act_veloc The actual velocity of the object. 
	*	@param time_delta_us The update period of the velocity. Time, which is passed
	*						 between two calculations.
	*	@return The actual velocity of an object.
	*/
	float calc_velocity(float angle, float act_veloc, const long long time_delta_us);
	
	/**
	*	Calculation of the distance of an object, which is moving with a given velocity.
	*	@param act_pos The actual position of the object. 
	*	@param act_veloc The actual velocity of the object, so the distance can be calculated.
	*					 calc_velocity has to be called first, so a velocity is calculated and
	*					 an angle is given.
	*	@param time_delta_us The update period of the velocity. Time, which is passed
	*						 between two calculations.
	*	@return actual distance
	*			The previous distance (act_pos) is added to the calculated one, so new
	*			distance in a given time period is returned.
	*/
	float calc_position(float act_pos, float act_veloc, const long long time_delta_us);

private:
	const float g_;
	float act_vel_;
	float act_acc_;
	const float low_limit_angle_;
	const float high_limit_angle_;
	
};

