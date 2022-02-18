#include "instruction.h"

Instruction::Instruction(RegisterController &registerController,
                         BusController &busController)
    : registerController{registerController}, busController{busController} {}

/*
LDA - Load Accumulator from Memory
M -> A (Group One)
Data from memory is transferred to the accumulator
Affects the accumulator, zero flag and negative flag
*/
void Instruction::LDA_Absolute(uint8_t address) {
  uint8_t memoryValue = busController.read(address);
  // TODO Set the status flag
  registerController.setRegisterValue(A, memoryValue);
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
