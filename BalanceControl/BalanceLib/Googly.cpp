#include "Googly.h"


Googly::Googly(float radius, float position, float velocity)
{
	radius_ = radius;
	position_ = position;
	velocity_ = velocity; 
}

void Googly::set_velocity(float velocity)
{
	velocity_ = velocity;
}

float Googly::get_velocity() const
{
	return velocity_;
}

void Googly::set_position(float position)
{
	position_ = position;
}

float Googly::get_position() const
{
	return position_;
}

Googly::~Googly()
{
}
