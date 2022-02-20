#include "../register/registercontroller.h"
#include "../bus/buscontroller.h"
#include <stdint.h>

#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

class Instruction {
private:
  RegisterController &registerController;
  BusController &busController;

public:
  Instruction(RegisterController &registerController, BusController &busController);
  uint8_t absolute(uint16_t address);
  void LDA(uint8_t value);
  void STA(uint16_t address);
};

#endif // __INSTRUCTION_H__