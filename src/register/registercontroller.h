#include "model/register.h"
#include "model/statusregister.h"
#include <stdint.h>

enum Registers {
  A = 0,
  STATUS,
  // Current size of the enum
  STATE_COUNT
};

#ifndef __REGISTERCONTROLLER_H__
#define __REGISTERCONTROLLER_H__

class RegisterController {
private:
StatusRegister *statusRegister;
  Register **registerArray;

public:
  RegisterController();
  uint8_t getRegisterValue(Registers registerIndex);
  StatusRegister *getStatusRegister();
  void setRegisterValue(Registers registerIndex, uint8_t value);
  ~RegisterController();
};

#endif // __REGISTERCONTROLLER_H__