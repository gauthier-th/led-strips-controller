#include "infrared_receiver.h"

InfraredReceiver::InfraredReceiver(WhiteStripController _white_strip_controller) : white_strip_controller(_white_strip_controller), ir_recv(IRrecv(pin_receiver))
{}

void InfraredReceiver::init()
{
  ir_recv.enableIRIn();  // Start the receiver
}

bool InfraredReceiver::loop()
{
  if (ir_recv.decode(&results))
  {
    ir_recv.resume();
    bool changed = false;

    if (results.command == 0x2)
    {
      white_strip_controller.set_power(false);
      changed = true;
    }
    else if (results.command == 0x3)
    {
      white_strip_controller.set_power(true);
      changed = true;
    }

    if (changed) {
      white_strip_controller.update();
    }
  }
  return true;
}