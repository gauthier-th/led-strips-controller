#pragma once
#include <Arduino.h>

class Controller
{
private:
public:
	/**
	 * Constructor
	 */
	Controller();
	void init();

	void setLight(int pin, int ratio);
};
