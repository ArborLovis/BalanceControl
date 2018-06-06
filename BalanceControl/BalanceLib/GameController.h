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

	void update_values();

private:
	Googly ball_;
	Physics physics_;
	Rocker seesaw_;
	Stabilizer controller_;
}; 

