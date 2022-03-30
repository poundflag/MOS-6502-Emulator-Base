#include "../../bus/buscontroller.h"
#include "register.h"

#ifndef __STACK_H__
#define __STACK_H__

class Stack : public Register {
private:
  BusController &busController;

public:
  Stack(BusController &busController);
  void push(uint8_t data);
  uint8_t pull();
  void pushWord(uint16_t data);
  uint16_t pullWord();
};

#endif // __STACK_H__