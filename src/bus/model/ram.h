#include "busdevice.h"
#include <stdint.h>

#ifndef __RAM_H__
#define __RAM_H__

class Ram : public BusDevice {
private:
uint8_t *ramArray;
uint16_t ramSize;
public:
  Ram(uint16_t ramSize);
  uint8_t read(uint16_t address);
  void write(uint16_t address, uint8_t value);
  ~Ram();
};

#endif // __RAM_H__