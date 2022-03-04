#include "register.h"
#include <iostream>

#ifndef __STATUSREGISTER_H__
#define __STATUSREGISTER_H__

enum Flag {
  Carry = 0,
  Zero,
  Interrupt,
  DecimalMode,
  BreakSignal,
  Bit5,
  Overflow,
  Negative
};

class StatusRegister : public Register {
public:
  StatusRegister();
  void setValue(uint8_t value1, uint8_t value2);
  void overrideValue(uint8_t value);
  void setCarry(uint16_t value);
  void setZero(uint8_t value);
  void setOverflow(uint8_t value1, uint8_t value2);
  void setNegative(uint8_t value);
  void setStatus(Flag flag, bool state);
  bool getStatus(Flag flag);
};

#endif // __STATUSREGISTER_H__