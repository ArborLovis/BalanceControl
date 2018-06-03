#include "stdafx.h"
#include "CppUnitTest.h"
#include "../BalanceLib/"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BalanceTest
{		
	TEST_CLASS(CLASS_PHYSICS_TEST)
	{
	public:
		
		TEST_METHOD(TestConstructor)
		{
			auto const sys_clk_rep = std::chrono::system_clock::now().time_since_epoch();
			//sys_rep_us time_us = std::chrono::duration_cast<std::chrono::microseconds>(sys_clk_rep).count();
			
			Physics make_stuff(0.003, sys_clk_rep);

			Assert::IsTrue(make_stuff.dummy_physics());
		}

	};
}