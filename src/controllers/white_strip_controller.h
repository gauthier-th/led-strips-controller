#pragma once
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class WhiteStripController
{
private:
	// Config
	int pin_strip = 1;

	// Strip state
	bool led_on = false;
	int led_brightness = 255; // 0-255
public:
	/**
	 * Constructor
	 */
	WhiteStripController();
	void init();
	void update();

	void set_power(bool state);
	void set_brightness(int brightness);

	bool get_power();
	int get_brightness();
};
