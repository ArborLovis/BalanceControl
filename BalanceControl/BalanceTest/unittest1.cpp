#include "stdafx.h"
#include "CppUnitTest.h"
#include "../BalanceLib/Physics.h"
#include "../BalanceLib/Stabilizer.h"
#include "../BalanceLib/Googly.h"
#include <iostream>



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BalanceTest
{		
	TEST_CLASS(CLASS_PHYSICS_TEST)
	{
	public:
		
		TEST_METHOD(velocity_by_uncahnged_angle)
		{	
			Physics phy_calculator;
			const auto time_delta_us = 10000;

			Assert::AreEqual(0.0, static_cast<double>(phy_calculator.calc_velocity(0.0f, 0, time_delta_us)));
			Assert::AreEqual(10.0, static_cast<double>(phy_calculator.calc_velocity(0.0f, 10.0f, time_delta_us)));
		}

		TEST_METHOD(velocity_by_pos_changed_angle)
		{			
			Physics phy_calculator;

			auto time_delta_us = 100000;	//simulate time delta of 100ms
			Assert::IsTrue(0.17 < phy_calculator.calc_velocity(10.0f, 0, time_delta_us));

			const auto vel = phy_calculator.calc_velocity(10.0f, 0, time_delta_us);
			time_delta_us += 100000;
			Assert::IsTrue(0.34 < phy_calculator.calc_velocity(10.0f, vel, time_delta_us));
		}

		TEST_METHOD(velocity_by_neg_changed_angle)
		{
			Physics phy_calculator;

			auto time_delta_us = 100000;	//simulate time delta of 100ms
			Assert::IsTrue(0.17 > phy_calculator.calc_velocity(-10.0f, 0, time_delta_us));

			const auto vel = phy_calculator.calc_velocity(-10.0f, 0, time_delta_us);
			time_delta_us += 100000;
			Assert::IsTrue(0.34 > phy_calculator.calc_velocity(-10.0f, vel, time_delta_us));
		}

		TEST_METHOD(velocity_limit_angle)
		{
			Physics phy_calculator;

			const auto time_delta_us = 100000;	//simulate time delta of 100ms
			auto act_vel = phy_calculator.calc_velocity(95.0f, 0, time_delta_us);
			
			Assert::IsTrue((0.982 > act_vel) && (0.980 < act_vel));

			act_vel = phy_calculator.calc_velocity(110.8f, 0, time_delta_us);
			act_vel = phy_calculator.calc_velocity(-15.0f, act_vel, time_delta_us);

			Assert::IsTrue(0.727 < act_vel && 0.7272 > act_vel);
		}

		TEST_METHOD(change_position)
		{
			Physics phy_calc;

			const auto time_delta_us = 1e3;	//1ms
			auto act_pos = 0.0f;
			auto act_vel = 0.0f;

			act_pos = phy_calc.calc_position(act_pos, 0, time_delta_us);
			act_vel = phy_calc.calc_velocity(20, act_vel, time_delta_us);
			Assert::AreEqual(0.0, static_cast<double>(act_pos));

			//starting at 0m by an initial angle of 20deg
			//ball should have moved 2m after 1,092s --> a = g*sin(alpha) --> v = a*dt --> s = v*dt/2
			//t = sqrt(2*2m/(9.81m/s^2 * sin(20))) = 1.092s
			for(auto cnt_time = 0; cnt_time < 1092; ++cnt_time)
			{
				act_vel = phy_calc.calc_velocity(20, act_vel, time_delta_us);
				act_pos = phy_calc.calc_position(act_pos, act_vel, time_delta_us);
			}
			Assert::IsTrue(1.9 < act_pos && 2.1 > act_pos);

			//change angle to -30deg
			//previous velocity: v = 9.81 * sin(20) * 1.092 = 3.66 m/s
			//brake after direction change: 3.66 m/s = 9.81 * sin(-30) * t --> t = 746,88s
			for (auto cnt_time = 0; cnt_time < 747; ++cnt_time)
			{
				act_vel = phy_calc.calc_velocity(-30, act_vel, time_delta_us);
				act_pos = phy_calc.calc_position(act_pos, act_vel, time_delta_us);
			}
			//vel. changes at 3.66 m/s --> the ball still roles 1.368 m until vel. gets zero
			// s = 3.66 m/s * 0.747 s / 2
			Assert::IsTrue(3.36 < act_pos && 3.38 > act_pos);
			Assert::IsTrue(-0.1 < act_vel && 0.1 > act_vel);
		}
	};

	TEST_CLASS(Class_stabilizer_test)
	{
	public:
		const float kp_test = 1;
		const float ki_test = 0.001;
		const float kd_test = 0.005;

		const float min_angle_test = -30;
		const float max_angle_test = 30;
		const float cycle_time_test = 5000;

		Stabilizer test_pid{ 0, 0, 0, min_angle_test, max_angle_test, cycle_time_test };

		TEST_METHOD(test_pid_constructor)
		{
			Assert::AreEqual(0, test_pid.get_kp(), 0, nullptr, nullptr);
			Assert::AreEqual(0, test_pid.get_ki(), 0, nullptr, nullptr);
			Assert::AreEqual(0, test_pid.get_kd(), 0, nullptr, nullptr);
		}

		TEST_METHOD(set_pid_values)
		{
			test_pid.set_kp(kp_test);
			Assert::AreEqual(kp_test, test_pid.get_kp(), 0, nullptr, nullptr);

			test_pid.set_ki(ki_test);
			Assert::AreEqual(ki_test, test_pid.get_ki(), 0, nullptr, nullptr);

			test_pid.set_kd(kd_test);
			Assert::AreEqual(kd_test, test_pid.get_kd(), 0, nullptr, nullptr);
		}

		TEST_METHOD(calc_setpoint_test)
		{
			test_pid.set_kp(kp_test);
			test_pid.set_ki(ki_test);
			test_pid.set_kd(kd_test);

			const auto position_test = 1;
			const auto error = 0 - position_test;
			const auto calc_return_value = error * kp_test + error * ki_test * cycle_time_test + (error - 0) * kd_test / cycle_time_test;

			Assert::AreEqual(calc_return_value, test_pid.calc_setpoint(position_test), 0, nullptr, nullptr);
		}
	};

	TEST_CLASS(test_class_googly)
	{

	};
}