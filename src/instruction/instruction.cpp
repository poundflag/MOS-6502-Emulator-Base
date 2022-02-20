#include "instruction.h"

Instruction::Instruction(RegisterController &registerController,
                         BusController &busController)
    : registerController{registerController}, busController{busController} {}

uint8_t Instruction::absoluteToImmediate(uint16_t address) {
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
STA - Store Accumulator in Memory
(A -> M) (Group One)
Stores data from the accumulator to memory
Doesn’t affect anything
*/
void Instruction::STA_Absolute(uint8_t address) {
  uint8_t aValue = registerController.getRegisterValue(A);
  busController.write(address, aValue);
}
