#include "stdafx.h"
#include "CppUnitTest.h"
#include "LedDriver.h"
#include "TestExtensions.h"
#include "RuntimeErrorStub.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LedlightTests
{		
	TEST_CLASS(UnitTest1)
	{		
	public:
		uint16_t virtualLeds;

		TEST_METHOD_INITIALIZE(SetupLeds)
		{
			LedDriver_Create(&virtualLeds);
		}

		TEST_METHOD(LedsOffAfterCreate)
		{
			uint16_t virtualLeds = 0xffff;
			LedDriver_Create(&virtualLeds);
			Assert::AreEqual(static_cast<uint16_t>(0), virtualLeds);
		}

		TEST_METHOD(TurnOnLedOne)
		{
			LedDriver_TurnOn(1);
			Assert::AreEqual(static_cast<uint16_t>(1), virtualLeds);
		}

		TEST_METHOD(TurnOffLedOne)
		{
			LedDriver_TurnOn(1);
			LedDriver_TurnOff(1);
			Assert::AreEqual(static_cast<uint16_t>(0), virtualLeds);
		}

		TEST_METHOD(TurnOnMultipleLeds)
		{
			LedDriver_TurnOn(9);
			LedDriver_TurnOn(8);
			Assert::AreEqual(static_cast<uint16_t>(0x180), virtualLeds);
		}

		TEST_METHOD(AllOn)
		{
			LedDriver_TurnAllOn();
			Assert::AreEqual(static_cast<uint16_t>(0xffff), virtualLeds);
		}

		TEST_METHOD(TurnOffAnyLed)
		{
			LedDriver_TurnAllOn();
			LedDriver_TurnOff(8);
			Assert::AreEqual(static_cast<uint16_t>(0xff7f), virtualLeds);
		}

		TEST_METHOD(LedMemoryIsNotReadable)
		{
			virtualLeds = 0xffff;
			LedDriver_TurnOn(8);
			Assert::AreEqual(static_cast<uint16_t>(0x80), virtualLeds);
		}

		TEST_METHOD(UpperAndLowerBounds)
		{
			LedDriver_TurnOn(1);
			LedDriver_TurnOn(16);
			Assert::AreEqual(static_cast<uint16_t>(0x8001), virtualLeds);
		}

		TEST_METHOD(OutOfBoundsChangesNothing)
		{
			LedDriver_TurnOn(-1);
			LedDriver_TurnOn(0);
			LedDriver_TurnOn(17);
			LedDriver_TurnOn(3141);
			Assert::AreEqual(static_cast<uint16_t>(0), virtualLeds);
		}

		TEST_METHOD(OutOfBoundsTurnOffDoesNoHarm)
		{
			LedDriver_TurnAllOn();
			LedDriver_TurnOff(-1);
			LedDriver_TurnOff(0);
			LedDriver_TurnOff(17);
			LedDriver_TurnOff(3141);
			Assert::AreEqual(static_cast<uint16_t>(0xffff), virtualLeds);
		}

		TEST_METHOD(OutOfBoundsProducesRuntimeError)
		{
			LedDriver_TurnOn(-1);
			Assert::AreEqual("LED Driver: out-of-bounds LED", RuntimeErrorStub_GetLastError());
			Assert::AreEqual(-1, RuntimeErrorStub_GetLastParameter());
		}

		TEST_METHOD(IsOn)
		{
			Assert::IsFalse(LedDriver_IsOn(11));
			LedDriver_TurnOn(11);
			Assert::IsTrue(LedDriver_IsOn(11));
		}

		TEST_METHOD(IsOff)
		{
			Assert::IsTrue(LedDriver_IsOff(12));
			LedDriver_TurnOn(12);
			Assert::IsFalse(LedDriver_IsOff(12));
		}

		TEST_METHOD(OutOfBoundsLedsAreAlwaysOff)
		{
			Assert::IsTrue(LedDriver_IsOff(0));
			Assert::IsTrue(LedDriver_IsOff(17));
			Assert::IsFalse(LedDriver_IsOn(0));
			Assert::IsFalse(LedDriver_IsOn(17));
		}

		TEST_METHOD(TurnOffMultipleLeds)
		{
			LedDriver_TurnAllOn();
			LedDriver_TurnOff(9);
			LedDriver_TurnOff(8);
			Assert::AreEqual(static_cast<uint16_t>((~0x180)&0xffff), virtualLeds);
		}

		TEST_METHOD(AllOff)
		{
			LedDriver_TurnAllOn();
			LedDriver_TurnAllOff();
			Assert::AreEqual(static_cast<uint16_t>(0), virtualLeds);
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(OutOfBoundsToDo)
			TEST_IGNORE()
		END_TEST_METHOD_ATTRIBUTE()
		TEST_METHOD(OutOfBoundsToDo)
		{
			// WHAT SHOULD WE DO DURING RUNTIME???
		}


	};
}