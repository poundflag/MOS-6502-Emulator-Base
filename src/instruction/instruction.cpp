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
LDX - LDX Load index X with memory

Operation:  M -> X   N Z C I D V
                     / / _ _ _ _
*/
void Instruction::LDX(uint8_t value) {
  // TODO Refactor
  registerController.setRegisterValue(X, value);
  registerController.getStatusRegister()->setZero(value);
  registerController.getStatusRegister()->setNegative(value);
}

/*
LDY - LDY Load index Y with memory
Operation:  M -> Y   N Z C I D V
                     / / _ _ _ _
*/
void Instruction::LDY(uint8_t value) {
  // TODO Refactor
  registerController.setRegisterValue(Y, value);
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

/*
STX - STX Store index X in memory

Operation: X -> M    N Z C I D V
                     _ _ _ _ _ _
*/
void Instruction::STX(uint16_t address) {
  uint8_t xValue = registerController.getRegisterValue(X);
  busController.write(address, xValue);
}

/*
STY - STY Store index Y in memory

Operation: Y -> M    N Z C I D V
                     _ _ _ _ _ _
*/
void Instruction::STY(uint16_t address) {
  uint8_t yValue = registerController.getRegisterValue(Y);
  busController.write(address, yValue);
}

/*
CLC - CLC Clear carry flag

Operation:  0 -> C   N Z C I D V
                     _ _ 0 _ _ _
*/
void Instruction::CLC() {
  registerController.getStatusRegister()->setStatus(Carry, false);
}

/*
CLD - CLD Clear decimal mode

Operation:  0 -> D   N A C I D V
                     _ _ _ _ 0 _
*/
void Instruction::CLD() {
  registerController.getStatusRegister()->setStatus(DecimalMode, false);
}

/*
CLI - CLI Clear interrupt disable bit

Operation: 0 -> I    N Z C I D V
                     _ _ _ 0 _ _
*/
void Instruction::CLI() {
  registerController.getStatusRegister()->setStatus(Interrupt, false);
}

/*
CLV - CLV Clear overflow flag

Operation: 0 -> V    N Z C I D V
                     _ _ _ _ _ 0
*/
void Instruction::CLV() {
  registerController.getStatusRegister()->setStatus(Overflow, false);
}

/*
SEC - SEC Set carry flag

Operation:  1 -> C   N Z C I D V
                     _ _ 1 _ _ _
*/
void Instruction::SEC() {
  registerController.getStatusRegister()->setStatus(Carry, true);
}

/*
SED - SED Set decimal mode

Operation:  1 -> D   N Z C I D V
                     _ _ _ _ 1 _
*/
void Instruction::SED() {
  registerController.getStatusRegister()->setStatus(DecimalMode, true);
}

/*
SEI - SEI Set interrupt disable status

Operation:  1 -> I   N Z C I D V
                     _ _ _ 1 _ _
*/
void Instruction::SEI() {
  registerController.getStatusRegister()->setStatus(Interrupt, true);
}

/*
DEC - DEC Decrement memory by one

Operation:  M - 1 -> M   N Z C I D V
                         / / _ _ _ _
*/
void Instruction::DEC(uint16_t address) {
  uint8_t data = busController.read(address);
  data--;
  busController.write(address, data);
  registerController.getStatusRegister()->setNegative(data);
  registerController.getStatusRegister()->setZero(data);
}

/*
DEX - DEX Decrement index X by one

Operation:  X - 1 -> X   N Z C I D V
                         / / _ _ _ _
*/
void Instruction::DEX() {
  uint8_t data = registerController.getRegisterValue(X);
  data--;
  registerController.setRegisterValue(X, data);
  registerController.getStatusRegister()->setNegative(data);
  registerController.getStatusRegister()->setZero(data);
}

/*
DEY - DEY Decrement index Y by one

Operation:  X - 1 -> Y   N Z C I D V
                         / / _ _ _ _
*/
void Instruction::DEY() {
  uint8_t data = registerController.getRegisterValue(Y);
  data--;
  registerController.setRegisterValue(Y, data);
  registerController.getStatusRegister()->setNegative(data);
  registerController.getStatusRegister()->setZero(data);
}

/*
INC - INC Increment memory by one

Operation:  M + 1 -> M   N Z C I D V
                         / / _ _ _ _
*/
void Instruction::INC(uint16_t address) {
  uint8_t data = busController.read(address);
  data++;
  busController.write(address, data);
  registerController.getStatusRegister()->setNegative(data);
  registerController.getStatusRegister()->setZero(data);
}

/*
INX - INX Increment Index X by one

Operation:  X + 1 -> X   N Z C I D V
                         / / _ _ _ _
*/
void Instruction::INX() {
  uint8_t data = registerController.getRegisterValue(X);
  data++;
  registerController.setRegisterValue(X, data);
  registerController.getStatusRegister()->setNegative(data);
  registerController.getStatusRegister()->setZero(data);
}

/*
INY - INY Increment Index Y by one

Operation:  X + 1 -> X   N Z C I D V
                         / / _ _ _ _
*/
void Instruction::INY() {
  uint8_t data = registerController.getRegisterValue(Y);
  data++;
  registerController.setRegisterValue(Y, data);
  registerController.getStatusRegister()->setNegative(data);
  registerController.getStatusRegister()->setZero(data);
}

/*
AND - "AND" memory with accumulator

Operation:  A /\ M -> A   N Z C I D V
                          / / _ _ _ _
*/
void Instruction::AND(uint16_t address) {
  uint8_t aValue = registerController.getRegisterValue(A);
  uint8_t memoryValue = busController.read(address);
  uint8_t result = aValue & memoryValue;
  registerController.setRegisterValue(A, result);
  registerController.getStatusRegister()->setNegative(result);
  registerController.getStatusRegister()->setZero(result);
}

/*
EOR - EOR "Exclusive-Or" memory with accumulator

Operation:  A EOR M -> A   N Z C I D V
                           / / _ _ _ _
*/
void Instruction::EOR(uint16_t address) {
  uint8_t aValue = registerController.getRegisterValue(A);
  uint8_t memoryValue = busController.read(address);
  uint8_t result = aValue ^ memoryValue;
  registerController.setRegisterValue(A, result);
  registerController.getStatusRegister()->setNegative(result);
  registerController.getStatusRegister()->setZero(result);
}