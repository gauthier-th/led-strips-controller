#pragma once
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include "controllers/white_strip_controller.h"

class InfraredReceiver
{
private:
  int pin_receiver = 0;
  IRrecv ir_recv;
  decode_results results;
  WhiteStripController white_strip_controller;
public:
  InfraredReceiver(WhiteStripController _white_strip_controller);
  void init();
  bool loop();
};