#include "register/model/register.h"
#include "register/model/statusregister.h"
#include "register/registercontroller.h"
#include <iostream>

#ifndef __ALU_H__
#define __ALU_H__

class ALU {
private:
  RegisterController &registerController;

public:
  ALU(RegisterController &registerController);
  uint8_t addOperation(uint8_t inputA, uint8_t inputB);
  uint8_t subOperation(uint8_t inputA, uint8_t inputB);
  uint8_t shiftLeftOperation(uint8_t inputA);
  uint8_t shiftRightOperation(uint8_t inputA);
  uint8_t andOperation(uint8_t inputA, uint8_t inputB);
};

#endif // __ALU_H__