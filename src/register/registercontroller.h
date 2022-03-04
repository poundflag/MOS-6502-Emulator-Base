#include "model/register.h"
#include "model/stack.h"
#include "model/statusregister.h"
#include "../bus/buscontroller.h"
#include <stdint.h>

#ifndef __REGISTERCONTROLLER_H__
#define __REGISTERCONTROLLER_H__

enum Registers {
  A = 0,
  X,
  Y,
  // Current size of the enum
  STATE_COUNT
};

class RegisterController {
private:
  StatusRegister *statusRegister;
  Stack *stackRegister;
  Register *registerArray;

public:
  RegisterController(BusController &busController);
  uint8_t getRegisterValue(Registers registerIndex);
  StatusRegister *getStatusRegister();
  Stack *getStack();
  void setRegisterValue(Registers registerIndex, uint8_t value);
  ~RegisterController();
};

#endif // __REGISTERCONTROLLER_H__