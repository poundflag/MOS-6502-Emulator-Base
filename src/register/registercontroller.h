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
  PCL,
  PCH,
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
  void setRegisterValue(Registers registerIndex, uint8_t value);
  uint16_t getProgramCounter();
  void setProgramCounter(uint16_t address);
  void incrementProgramCounter();
  StatusRegister *getStatusRegister();
  Stack *getStack();
  ~RegisterController();
};

#endif // __REGISTERCONTROLLER_H__