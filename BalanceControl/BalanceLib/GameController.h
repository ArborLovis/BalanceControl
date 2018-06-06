#pragma once

#include "Googly.h"
#include "Physics.h"
#include "Rocker.h"
#include "Stabilizer.h"
#include <chrono>

const float PI = 3.141592;
using sys_now_duration = std::chrono::duration<long long, std::ratio<1, 1000000000>>;
sys_now_duration test = std::chrono::system_clock::duration::zero();

class GameController
{
public:
	GameController();



private:
	Googly ball_;
	Physics physics_ = Physics( 0,  test);
	Rocker seesaw_;
	Stabilizer controller;
}; 

