#include "alu.h"

ALU::ALU(RegisterController &registerController)
    : registerController{registerController} {}

uint8_t ALU::addOperation(uint8_t inputA, uint8_t inputB) {
  bool carry = registerController.getStatusRegister()->getStatus(Carry);
  registerController.getStatusRegister()->setValue(inputA, inputB);

  return inputA + inputB + carry;
}

uint8_t ALU::subOperation(uint8_t inputA, uint8_t inputB) {
  bool carry = registerController.getStatusRegister()->getStatus(Carry);
  uint8_t result = addOperation(inputA, (~inputB) + 1);
  bool carry1 = registerController.getStatusRegister()->getStatus(Carry);
  if (carry == carry1) {
    registerController.getStatusRegister()->setStatus(Carry, true);
  }

  uint8_t m = inputB;
	unsigned int tmp = A - m - (registerController.getStatusRegister()->getStatus(Carry) ? 0 : 1);
	registerController.getStatusRegister()->setStatus(Overflow, !(((A ^ tmp) & 0x80) && ((A ^ m) & 0x80)));
  return result -1;
}

uint8_t ALU::shiftLeftOperation(uint8_t inputA) {
  registerController.getStatusRegister()->setStatus(Carry,
                                                    (inputA & 0x80) == 0x80);
  registerController.getStatusRegister()->setStatus(Zero,
                                                    (inputA & 0x80) == 0x80);
  inputA <<= 1;
  registerController.getStatusRegister()->setNegative(inputA);
  return inputA;
}

uint8_t ALU::shiftRightOperation(uint8_t inputA) {
  registerController.getStatusRegister()->setStatus(Carry, (inputA & 1) == 0x1);
  registerController.getStatusRegister()->setStatus(Zero, (inputA & 1) == 0x1);
  return inputA >> 1;
}

uint8_t ALU::andOperation(uint8_t inputA, uint8_t inputB) {
  uint8_t result = inputA & inputB;
  registerController.getStatusRegister()->setNegative(result);
  registerController.getStatusRegister()->setZero(result);
  return result;
}
