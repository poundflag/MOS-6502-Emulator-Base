#include "instruction.h"

Instruction::Instruction(RegisterController &registerController)
    : registerController{registerController} {}

/*
LDA - Load Accumulator from Memory
M -> A (Group One)
Data from memory is transferred to the accumulator
Affects the accumulator, zero flag and negative flag
*/
void Instruction::LDA_Absolute(uint8_t address) {}
