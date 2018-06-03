#include "stdafx.h"
#include "CppUnitTest.h"
#include "../BalanceLib/Physics.h"
#include "../BalanceLib/Stabilizer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BalanceTest
{		
	TEST_CLASS(CLASS_PHYSICS_TEST)
	{
	public:
		
		TEST_METHOD(TestConstructor)
		{
			sys_now_duration const clk_rep_cnt = std::chrono::system_clock::now().time_since_epoch();
						
			Physics make_stuff(static_cast<float>(0.003), clk_rep_cnt);

			Assert::IsTrue(make_stuff.dummy_physics());
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
}