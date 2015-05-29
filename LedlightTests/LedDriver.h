#pragma once

void LedDriver_Create(uint16_t* virtualLeds);

void LedDriver_TurnOn(int ledNumber);

void LedDriver_TurnOff(int ledNumber);

void LedDriver_TurnAllOn(void);

void LedDriver_TurnAllOff();

bool LedDriver_IsOn(int ledNumber);

bool LedDriver_IsOff(int ledNumber);