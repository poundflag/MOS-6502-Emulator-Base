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

/*
ORA - ORA "OR" memory with accumulator

Operation: A V M -> A   N Z C I D V
                        / / _ _ _ _
*/
void Instruction::ORA(uint16_t address) {
  uint8_t aValue = registerController.getRegisterValue(A);
  uint8_t memoryValue = busController.read(address);
  uint8_t result = aValue | memoryValue;
  registerController.setRegisterValue(A, result);
  registerController.getStatusRegister()->setNegative(result);
  registerController.getStatusRegister()->setZero(result);
}

/*
TAX - TAX Transfer accumulator to index X

Operation:  A -> X   N Z C I D V
                     / / _ _ _ _
*/
void Instruction::TAX() {
  uint8_t aValue = registerController.getRegisterValue(A);
  registerController.setRegisterValue(X, aValue);
  registerController.getStatusRegister()->setNegative(aValue);
  registerController.getStatusRegister()->setZero(aValue);
}

/*
TAY - TAY Transfer accumulator to index Y

Operation:  A -> Y   N Z C I D V
                     / / _ _ _ _
*/
void Instruction::TAY() {
  uint8_t aValue = registerController.getRegisterValue(A);
  registerController.setRegisterValue(Y, aValue);
  registerController.getStatusRegister()->setNegative(aValue);
  registerController.getStatusRegister()->setZero(aValue);
}

/*
TSX - Transfer stack pointer to index X

Operation:  S -> X   N Z C I D V
                     / / _ _ _ _
*/
void Instruction::TSX() {
  uint8_t stackValue = registerController.getStack()->pull();
  registerController.setRegisterValue(X, stackValue);
  registerController.getStatusRegister()->setNegative(stackValue);
  registerController.getStatusRegister()->setZero(stackValue);
}

/*
TXA - TXA Transfer index X to accumulator

Operation:  X -> A   N Z C I D V
                     / / _ _ _ _
*/
void Instruction::TXA() {
  uint8_t xValue = registerController.getRegisterValue(X);
  registerController.setRegisterValue(A, xValue);
  registerController.getStatusRegister()->setNegative(xValue);
  registerController.getStatusRegister()->setZero(xValue);
}

/*
TXS - TXS Transfer index X to stack pointer

Operation:  X -> S   N Z C I D V
                     _ _ _ _ _ _
*/
void Instruction::TXS() {
  uint8_t xValue = registerController.getRegisterValue(X);
  registerController.getStack()->push(xValue);
  registerController.getStatusRegister()->setNegative(xValue);
  registerController.getStatusRegister()->setZero(xValue);
}

/*
TYA - TYA Transfer index Y to accumulator

Operation:  Y -> A   N Z C I D V
                     / / _ _ _ _
*/
void Instruction::TYA() {
  uint8_t yValue = registerController.getRegisterValue(Y);
  registerController.setRegisterValue(A, yValue);
  registerController.getStatusRegister()->setNegative(yValue);
  registerController.getStatusRegister()->setZero(yValue);
}

/*
PHA - PHA Push accumulator on stack

Operation:  A to S   N Z C I D V
                     _ _ _ _ _ _
*/
void Instruction::PHA() {
  uint8_t aValue = registerController.getRegisterValue(A);
  registerController.getStack()->push(aValue);
}

/*
PHP - PHP Push processor status on stack

Operation:  P to S   N Z C I D V
                     _ _ _ _ _ _
*/
void Instruction::PHP() {
  uint8_t status = registerController.getStatusRegister()->getValue();
  registerController.getStack()->push(status);
}

/*
PLA - PLA Pull accumulator from stack

Operation:  A from S   N Z C I D V
                       _ _ _ _ _ _
*/
void Instruction::PLA() {
  registerController.setRegisterValue(A, registerController.getStack()->pull());
}

/*
PLP - PLP Pull processor status from stack

Operation:  P from S   N Z C I D V
                       From Stack
*/
void Instruction::PLP() {
  registerController.getStatusRegister()->Register::setValue(
      registerController.getStack()->pull());
}

/*
ADC - Add memory to accumulator with carry

Operation:  A + M + C -> A, C   N Z C I D V
                                / / / _ _ /
*/
void Instruction::ADC(uint8_t value) {
  bool carry = registerController.getStatusRegister()->getStatus(Carry);
  uint8_t aValue = registerController.getRegisterValue(A);
  registerController.getStatusRegister()->setValue(aValue, value);
  registerController.setRegisterValue(A, aValue + value + carry);
}

/*
ASL - Shift Left One Bit (Memory or Accumulator)

                   +-+-+-+-+-+-+-+-+
  Operation:  C <- |7|6|5|4|3|2|1|0| <- 0
                   +-+-+-+-+-+-+-+-+      N Z C I D V
                                          / / / _ _ _
*/
void Instruction::ASL_Memory(uint16_t memoryAddress) {
  // TODO Add later accumulator call
  // TODO Add ALU later
  uint8_t memoryValue = busController.read(memoryAddress);
  registerController.getStatusRegister()->setCarry((memoryValue & 0x80) == 0x80);
  memoryValue <<= 1;
  busController.write(memoryAddress, memoryValue);
}