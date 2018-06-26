#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>

#include "../BalanceLib/Physics.h"
#include "../BalanceLib/Stabilizer.h"
#include "../BalanceLib/Googly.h"
#include "../BalanceLib/Rocker.h"
#include "../BalanceLib/Math_const.h"

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

			//flat surface, no movement here
			Assert::AreEqual(0.0, static_cast<double>(phy_calculator.calc_velocity(0.0f, 0, time_delta_us)));
			Assert::AreEqual(10.0, static_cast<double>(phy_calculator.calc_velocity(0.0f, 10.0f, time_delta_us)));	//flat surface, init velocity and no friction
		}

		TEST_METHOD(velocity_by_pos_changed_angle)
		{			
			Physics phy_calculator;

			//expected output: g * sin(10�) * 0.1s = 0.17035
			auto time_delta_us = 100000;	//simulate time delta of 100ms
			Assert::IsTrue(0.17 < phy_calculator.calc_velocity(10.0f, 0, time_delta_us));

			const auto vel = phy_calculator.calc_velocity(10.0f, 0, time_delta_us);	//again 0.17 m/s
			time_delta_us += 100000;	//another 100ms passed
			Assert::IsTrue(0.34 < phy_calculator.calc_velocity(10.0f, vel, time_delta_us)); // expected output: twice of 0.17 m/s
		}

		TEST_METHOD(velocity_by_neg_changed_angle)	//same values expected as above, just with another sign
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
			
			Assert::IsTrue((0.982 > act_vel) && (0.980 < act_vel));	//limits within 90�

			//change in position and limits
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

	TEST_CLASS(Class_googly_test)
	{
		TEST_METHOD(test_googly_constructor)
		{
			const float test_radius = 1.0;
			const float test_position = 0;
			const float test_velocity = 0;

			Googly Ball{ test_radius, test_position, test_velocity };

			Assert::AreEqual(test_radius, Ball.get_radius());
			Assert::AreEqual(test_position, Ball.get_position());
			Assert::AreEqual(test_velocity, Ball.get_velocity());
		}

		TEST_METHOD(test_googly_set_velocity)
		{
			const float test_radius = 1.0;
			const float test_position = 0;
			const float test_velocity = 0;
			const float new_test_velocity = 5;

			Googly Ball{ test_radius, test_position, test_velocity };

			Ball.set_velocity(new_test_velocity);
			Assert::AreEqual(new_test_velocity, Ball.get_velocity());
		}

		TEST_METHOD(test_googly_set_position)
		{
			const float test_radius = 1.0;
			const float test_position = 0;
			const float test_velocity = 0;
			const float new_test_position = 5;

			Googly Ball{ test_radius, test_position, test_velocity };

			Ball.set_position(new_test_position);
			Assert::AreEqual(new_test_position, Ball.get_position());
		}
	};

	TEST_CLASS(Class_rocker_test)
	{
		TEST_METHOD(test_rocker_std_cotr)
		{
			Rocker test_rocker;
			const float time_delta = 100000.0f;	//100ms
			float act_angle = 0.0f;

			//check default value of angle
			Assert::AreEqual(0.0, static_cast<double>(test_rocker.get_angle(0)));

			//change of angle
			test_rocker.set_angle(pi / 8);	//change angle within the limits
			
			//pi/4 * e-6 -> max angle speed per �s
			// after 100ms --> 78.54e-3 rad/s
			// --> pi/8 will be reached after min. 0.5s
			for(auto i = 0; i < 6; i++)
				act_angle = test_rocker.get_angle(time_delta);	//check angle after 0.6s

			Assert::IsTrue((pi / 8 - 0.01f) < act_angle && act_angle < (pi / 8 + 0.01f));
		}

		TEST_METHOD(test_rocker_spez_cotr)
		{
			Rocker test_rocker(2.0f, pi / 10);
			const float time_delta = 10000.0f;	//10ms	(take a higher resolution)
			float act_angle = 0.0f;

			//check default value of angle
			act_angle = test_rocker.get_angle(time_delta);	//angle has to be const, so time does not matter
			Assert::IsTrue((pi / 10 - 0.01f) < act_angle && act_angle < (pi / 10 + 0.01f));

			//change of angle
			test_rocker.set_angle(- pi / 10);	//change angle within the limits

			//pi/4 * e-6 -> max angle speed per �s
			// after 10ms --> 7.854e-3 rad/s
			// --> -pi/10 will be reached after min. 0.8s
			for (auto i = 0; i < 90; i++)
				act_angle = test_rocker.get_angle(time_delta);	//check angle after 0.9s

			Assert::IsTrue((- pi / 10 - 0.01f) < act_angle && act_angle < (- pi / 10 + 0.01f));
		}

		TEST_METHOD(test_rocker_limits)
		{
			Rocker test_rocker;
			const float time_delta = 100000.0f;	//100ms
			float act_angle = 0.0f;
		
			//change of angle --> positive
			test_rocker.set_angle(pi / 3);	//exeed limits -> 60�

			//pi/4 * e-6 -> max angle speed per �s
			// after 100ms --> 78.54e-3 rad/s
			// --> pi/8 will be reached after min. 0.5s and so pi/3 would be reached 1.333s
			for (auto i = 0; i < 15; i++)
				act_angle = test_rocker.get_angle(time_delta);	//check angle after 1.5s

			//angle has to stuck at angle pi/8
			Assert::IsTrue((pi / 8 - 0.01f) < act_angle && act_angle < (pi / 8 + 0.01f));

			//change of angle --> negative
			test_rocker.set_angle(- pi / 3);	//exeed limits -> -60�

			// --> -pi/8 will be reached after min. 0.5s and so -pi/3 would be reached 1.333s
			for (auto i = 0; i < 30; i++)
				act_angle = test_rocker.get_angle(time_delta);	//check angle after 3s, twice 1.5s because angle stuck in pos. max. pos.

			//angle has to stuck at angle -pi/8
			Assert::IsTrue((- pi / 8 - 0.01f) < act_angle && act_angle < (- pi / 8 + 0.01f));
		}

		TEST_METHOD(test_rocker_cpy_assign_opr)
		{
			Rocker test_rocker;
			Rocker assigned_rocker;
			const float time_delta = 10000.0f;	//10ms
			float act_angle = 0.0f;

			test_rocker.set_angle(pi / 16);	//to reach an angle of pi/16 -> time slots has to be smaller, otherwise angle overshoot permanently 
			for (auto i = 0; i < 30; i++)
				act_angle = test_rocker.get_angle(time_delta);	//check angle after 0.3s

			Assert::IsTrue((pi / 16 - 0.01f) < act_angle && act_angle < (pi / 16 + 0.01f));
			Assert::AreEqual(0.0, static_cast<double>(assigned_rocker.get_angle(time_delta)));	//check if zero, even after some time
			
			//copy rocker obj and check if equal
			assigned_rocker = test_rocker;
			act_angle = assigned_rocker.get_angle(0.0f);
			Assert::IsTrue(pi / 16 - 0.01f < act_angle && act_angle < pi / 16 + 0.01f);
		}
	};
}
