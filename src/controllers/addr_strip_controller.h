#pragma once
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class AddrStripController
{
private:
	// Config
	int pin_strip = 1;
	int num_leds = 3;

	// Strip state
	bool led_on = false;
	int led_brightness = 255; // 0-255
	int led_red = 127;
	int led_green = 0;
	int led_blue = 127;
	int neopixel_mode = 0;  // 0-3
	int neopixel_speed = 0; // 0-3

	Adafruit_NeoPixel strip;

	// Animation functions
	void neo_dash();
	void neo_rainbow();
	void neo_colorWipe();
	void neo_fill_color();
public:
	/**
	 * Constructor
	 */
	AddrStripController();
	void init();
	void loop();

	void set_power(bool state);
	void set_brightness(int brightness);
	void set_color(int r, int g, int b);
	void set_mode(int mode);
	void set_speed(int speed);

	bool get_power();
	int get_brightness();
	std::tuple<int, int, int> get_color();
	int get_mode();
	int get_speed();
};
