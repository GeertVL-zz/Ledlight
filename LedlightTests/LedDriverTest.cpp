#include "stdafx.h"
#include "CppUnitTest.h"
#include "LedDriver.h"
#include "TestExtensions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LedlightTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(LedsOffAfterCreate)
		{
			uint16_t virtualLeds = 0xffff;
			LedDriver_Create(&virtualLeds);
			uint16_t expected = 0;
			Assert::AreEqual(expected, virtualLeds, L"the message", LINE_INFO());
		}
	};
}