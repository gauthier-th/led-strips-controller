#include "controller.h"

Controller::Controller()
{}

void Controller::init() {
	pinMode(0, OUTPUT);
}

void Controller::setLight(int pin, int ratio) {
  if (ratio < 0)
    analogWrite(0, 0);
  else if (ratio > 255)
    analogWrite(0, 255);
  else
    analogWrite(0, ratio);
}