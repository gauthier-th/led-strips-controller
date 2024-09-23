#include "rgb_strip_controller.h"

RgbStripController::RgbStripController()
{}

void RgbStripController::init()
{
	pinMode(pin_strip_r, OUTPUT);
	pinMode(pin_strip_g, OUTPUT);
	pinMode(pin_strip_b, OUTPUT);
}

void RgbStripController::update()
{
  if (led_on)
  {
    analogWrite(pin_strip_r, led_red * led_brightness / 255);
    analogWrite(pin_strip_g, led_green * led_brightness / 255);
    analogWrite(pin_strip_b, led_blue * led_brightness / 255);
  }
  else
  {
    analogWrite(pin_strip_r, 0);
    analogWrite(pin_strip_g, 0);
    analogWrite(pin_strip_b, 0);
  }
}

void RgbStripController::set_power(bool state)
{
  led_on = state;
}
void RgbStripController::set_brightness(int brightness)
{
  if (brightness < 0)
    led_brightness = 0;
  else if (brightness > 255)
    led_brightness = 255;
  else
    led_brightness = brightness;
}
void RgbStripController::set_color(int r, int g, int b)
{
  if (r < 0)
    led_red = 0;
  else if (r > 255)
    led_red = 255;
  else
    led_red = r;
  if (g < 0)
    led_green = 0;
  else if (g > 255)
    led_green = 255;
  else
    led_green = g;
  if (b < 0)
    led_blue = 0;
  else if (b > 255)
    led_blue = 255;
  else
    led_blue = b;
}

bool RgbStripController::get_power()
{
  return this->led_on;  
}
int RgbStripController::get_brightness()
{
  return this->led_on;  
}
std::tuple<int, int, int> RgbStripController::get_color()
{
  return std::make_tuple(this->led_red, this->led_green, this->led_blue);
}