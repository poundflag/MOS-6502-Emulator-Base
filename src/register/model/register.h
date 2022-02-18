#include <stdint.h>

#ifndef __REGISTER_H__
#define __REGISTER_H__

class Register {
protected:
  uint8_t value;

public:
  Register();
  virtual void setValue(uint8_t value);
  virtual uint8_t getValue();
};

#endif // __REGISTER_H__