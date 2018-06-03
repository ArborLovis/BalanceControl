#include "stdafx.h"
#include "CppUnitTest.h"
#include "../BalanceLib/Physics.h"

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
}