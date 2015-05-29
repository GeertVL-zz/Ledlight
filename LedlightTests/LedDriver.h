#pragma once


class LedDriver
{
	uint16_t* ledsAddress;
	uint16_t ledsImage;

	void updateHardware();
	bool IsLedOutOfBounds(int ledNumber);
	int convertLedNumberToBit(int ledNumber);
	void setLedImageBit(int ledNumber);
	void clearLedImageBit(int ledNumber);
public:
	void Create(uint16_t* virtualLeds);

	void TurnOn(int ledNumber);

	void TurnOff(int ledNumber);

	void TurnAllOn(void);

	void TurnAllOff();

	bool IsOn(int ledNumber);

	bool IsOff(int ledNumber);
};
