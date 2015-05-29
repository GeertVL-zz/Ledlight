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
		LedDriver* ledDriver;

		TEST_METHOD_INITIALIZE(SetupLeds)
		{
			ledDriver = new LedDriver;
			ledDriver->Create(&virtualLeds);
		}

		TEST_METHOD_CLEANUP(CleanupLeds)
		{
			delete ledDriver;
		}

		TEST_METHOD(LedsOffAfterCreate)
		{
			uint16_t virtualLeds = 0xffff;
			ledDriver->Create(&virtualLeds);
			Assert::AreEqual(static_cast<uint16_t>(0), virtualLeds);
		}

		TEST_METHOD(TurnOnLedOne)
		{
			ledDriver->TurnOn(1);
			Assert::AreEqual(static_cast<uint16_t>(1), virtualLeds);
		}

		TEST_METHOD(TurnOffLedOne)
		{
			ledDriver->TurnOn(1);
			ledDriver->TurnOff(1);
			Assert::AreEqual(static_cast<uint16_t>(0), virtualLeds);
		}

		TEST_METHOD(TurnOnMultipleLeds)
		{
			ledDriver->TurnOn(9);
			ledDriver->TurnOn(8);
			Assert::AreEqual(static_cast<uint16_t>(0x180), virtualLeds);
		}

		TEST_METHOD(AllOn)
		{
			ledDriver->TurnAllOn();
			Assert::AreEqual(static_cast<uint16_t>(0xffff), virtualLeds);
		}

		TEST_METHOD(TurnOffAnyLed)
		{
			ledDriver->TurnAllOn();
			ledDriver->TurnOff(8);
			Assert::AreEqual(static_cast<uint16_t>(0xff7f), virtualLeds);
		}

		TEST_METHOD(LedMemoryIsNotReadable)
		{
			virtualLeds = 0xffff;
			ledDriver->TurnOn(8);
			Assert::AreEqual(static_cast<uint16_t>(0x80), virtualLeds);
		}

		TEST_METHOD(UpperAndLowerBounds)
		{
			ledDriver->TurnOn(1);
			ledDriver->TurnOn(16);
			Assert::AreEqual(static_cast<uint16_t>(0x8001), virtualLeds);
		}

		TEST_METHOD(OutOfBoundsChangesNothing)
		{
			ledDriver->TurnOn(-1);
			ledDriver->TurnOn(0);
			ledDriver->TurnOn(17);
			ledDriver->TurnOn(3141);
			Assert::AreEqual(static_cast<uint16_t>(0), virtualLeds);
		}

		TEST_METHOD(OutOfBoundsTurnOffDoesNoHarm)
		{
			ledDriver->TurnAllOn();
			ledDriver->TurnOff(-1);
			ledDriver->TurnOff(0);
			ledDriver->TurnOff(17);
			ledDriver->TurnOff(3141);
			Assert::AreEqual(static_cast<uint16_t>(0xffff), virtualLeds);
		}

		TEST_METHOD(OutOfBoundsProducesRuntimeError)
		{
			ledDriver->TurnOn(-1);
			Assert::AreEqual("LED Driver: out-of-bounds LED", RuntimeErrorStub_GetLastError());
			Assert::AreEqual(-1, RuntimeErrorStub_GetLastParameter());
		}

		TEST_METHOD(IsOn)
		{
			Assert::IsFalse(ledDriver->IsOn(11));
			ledDriver->TurnOn(11);
			Assert::IsTrue(ledDriver->IsOn(11));
		}

		TEST_METHOD(IsOff)
		{
			Assert::IsTrue(ledDriver->IsOff(12));
			ledDriver->TurnOn(12);
			Assert::IsFalse(ledDriver->IsOff(12));
		}

		TEST_METHOD(OutOfBoundsLedsAreAlwaysOff)
		{
			Assert::IsTrue(ledDriver->IsOff(0));
			Assert::IsTrue(ledDriver->IsOff(17));
			Assert::IsFalse(ledDriver->IsOn(0));
			Assert::IsFalse(ledDriver->IsOn(17));
		}

		TEST_METHOD(TurnOffMultipleLeds)
		{
			ledDriver->TurnAllOn();
			ledDriver->TurnOff(9);
			ledDriver->TurnOff(8);
			Assert::AreEqual(static_cast<uint16_t>((~0x180) & 0xffff), virtualLeds);
		}

		TEST_METHOD(AllOff)
		{
			ledDriver->TurnAllOn();
			ledDriver->TurnAllOff();
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
