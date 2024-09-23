#include "addr_strip_controller.h"

AddrStripController::AddrStripController()
{}

void AddrStripController::init()
{
  strip = Adafruit_NeoPixel(num_leds, pin_strip, NEO_BRG + NEO_KHZ800);
  strip.begin();
}

void AddrStripController::loop()
{
  if (led_on)
  {
    if (neopixel_mode == 0)
      neo_fill_color();
    else if (neopixel_mode == 1)
      neo_colorWipe();
    else if (neopixel_mode == 2)
      neo_rainbow();
    else if (neopixel_mode == 3)
      neo_dash();
  }
  else
  {
    strip.fill(strip.gamma32(strip.Color(0, 0, 0)));
  }
}

void AddrStripController::set_power(bool state)
{
  led_on = state;
}
void AddrStripController::set_brightness(int brightness)
{
  if (brightness < 0)
    led_brightness = 0;
  else if (brightness > 255)
    led_brightness = 255;
  else
    led_brightness = brightness;
}
void AddrStripController::set_color(int r, int g, int b)
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
void AddrStripController::set_mode(int mode)
{
  if (mode < 0)
    neopixel_mode = 0;
  else if (mode > 3)
    neopixel_mode = 3;
  else
    neopixel_mode = mode;
}
void AddrStripController::set_speed(int speed)
{
  if (speed < 0)
    neopixel_speed = 0;
  else if (speed > 3)
    neopixel_speed = 3;
  else
    neopixel_speed = speed;
}


void AddrStripController::neo_fill_color()
{
  strip.fill(strip.gamma32(strip.Color(
      led_red * led_brightness / 255,
      led_green * led_brightness / 255,
      led_blue * led_brightness / 255)));
}

void AddrStripController::neo_colorWipe()
{
  float rate = ((3 - neopixel_speed) * 2) + 1; // number of seconds to complete a cycle
  float hue = map(millis(), 0, rate * 1000, 0, 65536);
  strip.fill(strip.gamma32(strip.ColorHSV(hue, 255, led_brightness)));
}

void AddrStripController::neo_rainbow()
{
  float rate = ((3 - neopixel_speed) * 2) + 1; // number of seconds to complete a cycle
  float start_hue = map(millis(), 0, rate * 1000, 0, 65536);
  for (int i = 0; i < num_leds; i++)
  {
    float hue = start_hue + (i * 65536 / num_leds);
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(hue, 255, led_brightness)));
  }
}

void AddrStripController::neo_dash()
{
  int dot_size = neopixel_speed == 0 ? 12 : (neopixel_speed == 1 ? 6 : 2);
  int amount = neopixel_speed == 0 ? 1 : (neopixel_speed == 1 ? 3 : 11);

  for (int i = 0; i < num_leds; i++)
  {
    strip.setPixelColor(i, 0);
  }

  int current_dot = map(millis(), 0, 1000 / amount, 0, num_leds / amount);

  for (int i = 0; i < amount; i++)
  {
    for (int j = 0; j < dot_size; j++)
    {
      int pixel_index = (current_dot + j + i * num_leds / amount) % num_leds;
      strip.setPixelColor(pixel_index, strip.gamma32(strip.Color(
                                          led_red * led_brightness / 255,
                                          led_green * led_brightness / 255,
                                          led_blue * led_brightness / 255)));
    }
  }
}

bool AddrStripController::get_power()
{
  return this->led_on;  
}
int AddrStripController::get_brightness()
{
  return this->led_on;
}
std::tuple<int, int, int> AddrStripController::get_color()
{
  return std::make_tuple(this->led_red, this->led_green, this->led_blue);
}
int AddrStripController::get_mode()
{
  return this->neopixel_mode;
}
int AddrStripController::get_speed()
{
  return this->neopixel_speed;
}