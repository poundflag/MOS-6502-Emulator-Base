#include "model/register.h"
#include <stdint.h>

enum Registers {
  A = 0,
  // Current size of the enum
  STATE_COUNT
};

#ifndef __REGISTERCONTROLLER_H__
#define __REGISTERCONTROLLER_H__

class RegisterController {
private:
  Register registerArray[STATE_COUNT];

public:
  uint8_t getRegisterValue(Registers registerIndex);
  void setRegisterValue(Registers registerIndex, uint8_t value);
};

#endif // __REGISTERCONTROLLER_H__