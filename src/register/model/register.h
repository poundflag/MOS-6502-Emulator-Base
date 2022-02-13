#include <stdint.h>

#ifndef __REGISTER_H__
#define __REGISTER_H__

class Register {
private:
  uint8_t value;

public:
  Register();
  void setValue(uint8_t value);
  uint8_t getValue();
};

#endif // __REGISTER_H__