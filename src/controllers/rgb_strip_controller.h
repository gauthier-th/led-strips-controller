#pragma once
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class RgbStripController
{
private:
	// Config
	int pin_strip_r = 1;
	int pin_strip_g = 2;
	int pin_strip_b = 3;

	// Strip state
	bool led_on = false;
	int led_brightness = 255; // 0-255
	int led_red = 127;
	int led_green = 0;
	int led_blue = 127;
public:
	/**
	 * Constructor
	 */
	RgbStripController();
	void init();
	void update();

	void set_power(bool state);
	void set_brightness(int brightness);
	void set_color(int r, int g, int b);

	bool get_power();
	int get_brightness();
	std::tuple<int, int, int> get_color();
};
