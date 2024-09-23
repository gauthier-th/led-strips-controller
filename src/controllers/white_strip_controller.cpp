#include "white_strip_controller.h"

WhiteStripController::WhiteStripController()
{}

void WhiteStripController::init()
{
	pinMode(pin_strip, OUTPUT);
  this->update();
}

void WhiteStripController::update()
{
  if (led_on)
    analogWrite(pin_strip, led_brightness);
  else
    analogWrite(pin_strip, 0);
}

void WhiteStripController::set_power(bool state)
{
  led_on = state;
}
void WhiteStripController::set_brightness(int brightness)
{
  if (brightness < 0)
    led_brightness = 0;
  else if (brightness > 255)
    led_brightness = 255;
  else
    led_brightness = brightness;
}

bool WhiteStripController::get_power()
{
  return this->led_on;
}
int WhiteStripController::get_brightness()
{
  return this->led_brightness;
}