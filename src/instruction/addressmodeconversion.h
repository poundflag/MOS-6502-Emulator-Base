#include "../bus/buscontroller.h"
#include "../register/registercontroller.h"

#ifndef __ADDRESSMODECONVERSION_H__
#define __ADDRESSMODECONVERSION_H__

class AddressModeConversion {
private:
  BusController &busController;
  RegisterController &registerController;

public:
  AddressModeConversion(RegisterController &registerController,
                        BusController &busController); // TODO Refactor later
  uint8_t absolute(uint16_t address);
  uint8_t absoluteXIndexed(uint16_t address);
  uint8_t absoluteYIndexed(uint16_t address);
  uint8_t zeroPage(uint8_t address);
  uint8_t zeroPageXIndexed(uint8_t address);
  uint8_t zeroPageYIndexed(uint8_t address);
  uint16_t absoluteIndirect(uint16_t address);
  uint8_t indexedIndirect(uint8_t address);
  uint8_t indirectIndexed(uint8_t address);
};

#endif // __ADDRESSMODECONVERSION_H__