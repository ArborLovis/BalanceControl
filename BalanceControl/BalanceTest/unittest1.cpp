#include "stdafx.h"
#include "CppUnitTest.h"
#include "../BalanceLib/Physics.h"
#include "../BalanceLib/Stabilizer.h"
#include "../BalanceLib/Googly.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BalanceTest
{		
	TEST_CLASS(CLASS_PHYSICS_TEST)
	{
	public:
		
		TEST_METHOD(velocity_by_uncahnged_angle)
		{
			sys_now_duration const clk_rep_cnt = std::chrono::system_clock::now().time_since_epoch();	
			Physics phy_calculator(0.0f, clk_rep_cnt);
		
			const long long time_now_us = std::chrono::duration_cast<std::chrono::microseconds>(clk_rep_cnt).count();
			Assert::AreEqual(0.0, static_cast<double>(phy_calculator.calc_velocity(0.0f, 0, time_now_us)));
		}

		TEST_METHOD(velocity_by_cahnged_angle)
		{
			bool exception_appear = false;
			try
			{
				sys_now_duration const clk_rep_cnt = std::chrono::system_clock::now().time_since_epoch();
				Physics phy_calculator(0.0f, clk_rep_cnt);

				auto time_now_us = std::chrono::duration_cast<std::chrono::microseconds>(clk_rep_cnt).count();
				//Assert::AreEqual(0.0, static_cast<double>(time_now_us));
				time_now_us += 100000;	//simulate time delta of 100ms

				//Assert::AreEqual(0.170349, static_cast<double>(phy_calculator.calc_velocity(10.0f, 0, time_now_us)));
				Assert::IsTrue(0.17 < phy_calculator.calc_velocity(10.0f, 0, time_now_us));
				const auto vel = phy_calculator.calc_velocity(10.0f, 0, time_now_us);
				time_now_us += 200000;
				Assert::IsTrue(0.34 < phy_calculator.calc_velocity(10.0f, vel, time_now_us));
				
			}
			catch(const std::exception &e)
			{
				exception_appear = true;
			}
			Assert::IsFalse(exception_appear);
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
}