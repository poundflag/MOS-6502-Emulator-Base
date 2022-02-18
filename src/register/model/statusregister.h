#include "register.h"

enum Status {
  Carry = 0,
  Zero,
  Interrupt,
  DecimalMode,
  BreakSignal,
  Bit5,
  Overflow,
  Sign
};

#ifndef __STATUSREGISTER_H__
#define __STATUSREGISTER_H__

class StatusRegister : public Register {
private:
public:
  StatusRegister();
  void processStatus(uint8_t value);
  bool getStatus(Status status);
};

#endif // __STATUSREGISTER_H__