#include "instruction.h"

Instruction::Instruction(RegisterController &registerController,
                         BusController &busController)
    : registerController{registerController}, busController{busController} {}

uint8_t Instruction::absolute(uint16_t address) {
  return busController.read(address);
}

/*
LDA - LDA Load accumulator with memory

Operation:  M -> A   N Z C I D V
                     / / _ _ _ _
Addressing Mode: Group One
*/
void Instruction::LDA(uint8_t value) {
  registerController.setRegisterValue(A, value);
  registerController.getStatusRegister()->setZero(value);
  registerController.getStatusRegister()->setNegative(value);
}

/*
STA - STA Store accumulator in memory

Operation:  A -> M   N Z C I D V
                     _ _ _ _ _ _
Addressing Mode: Group One
*/
void Instruction::STA(uint16_t address) {
  uint8_t aValue = registerController.getRegisterValue(A);
  busController.write(address, aValue);
}
