#include "register/registercontroller.h"
#include <stdint.h>

#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

class Instruction {
private:
  RegisterController &registerController;

public:
  Instruction(RegisterController &registerController);
  void LDA_Absolute(uint8_t address);
  void STA_Absolute(uint8_t address);
};

#endif // __INSTRUCTION_H__