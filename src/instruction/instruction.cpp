#include "instruction.h"

Instruction::Instruction(RegisterController &registerController,
                         BusController &busController, ALU &alu)
    : registerController{registerController},
      busController{busController}, alu{alu} {}

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
  uint8_t result = alu.andOperation(aValue, memoryValue);
  registerController.setRegisterValue(A, result);
}

/*
EOR - EOR "Exclusive-Or" memory with accumulator

Operation:  A EOR M -> A   N Z C I D V
                           / / _ _ _ _
*/
void Instruction::EOR(uint16_t address) {
  uint8_t aValue = registerController.getRegisterValue(A);
  uint8_t memoryValue = busController.read(address); // TODO NOT USED
  uint8_t result = aValue ^ address;                 //  TODO ALU?
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
  uint8_t stackValue = registerController.getStack()->getValue();
  uint8_t xValue = registerController.getRegisterValue(X);
  registerController.setRegisterValue(X, stackValue);
  registerController.getStatusRegister()->setNegative(stackValue);
  // registerController.getStatusRegister()->setZero(stackValue);
  registerController.getStatusRegister()->setStatus(Zero, xValue != stackValue);
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
  /*uint8_t xValue = registerController.getRegisterValue(X);
  registerController.getStack()->push(xValue);
  registerController.getStatusRegister()->setNegative(xValue);
  registerController.getStatusRegister()->setZero(xValue);*/
  uint8_t xValue = registerController.getRegisterValue(X);
  registerController.getStack()->setValue(xValue);
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
                       / / _ _ _ _
*/
void Instruction::PLA() {
  uint8_t aValue = registerController.getStack()->pull();
  registerController.setRegisterValue(A, aValue);
  registerController.getStatusRegister()->setNegative(aValue);
  registerController.getStatusRegister()->setZero(aValue);
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
  uint8_t aValue = registerController.getRegisterValue(A);
  uint8_t result = alu.addOperation(aValue, value);
  registerController.setRegisterValue(A, result);
}

/*
ASL - Shift Left One Bit (Memory or Accumulator)

                 +-+-+-+-+-+-+-+-+
Operation:  C <- |7|6|5|4|3|2|1|0| <- 0
                 +-+-+-+-+-+-+-+-+    N Z C I D V
                                      / / / _ _ _
*/
void Instruction::ASL_Memory(uint16_t memoryAddress) {
  uint8_t memoryValue = busController.read(memoryAddress);
  busController.write(memoryAddress, alu.shiftLeftOperation(memoryValue));
}

void Instruction::ASL_Accumulator() {
  uint8_t accValue = registerController.getRegisterValue(A);
  registerController.setRegisterValue(A, accValue);
}

/*
LSR - Shift right one bit (memory or accumulator)

                 +-+-+-+-+-+-+-+-+
Operation:  0 -> |7|6|5|4|3|2|1|0| -> C
                 +-+-+-+-+-+-+-+-+    N Z C I D V
                                      0 / / _ _ _

*/
void Instruction::LSR_Memory(uint16_t memoryAddress) {
  uint8_t memoryValue = busController.read(memoryAddress);
  busController.write(memoryAddress, alu.shiftRightOperation(memoryValue));
}

void Instruction::LSR_Accumulator() {
  uint8_t accValue = registerController.getRegisterValue(A);
  registerController.setRegisterValue(A, alu.shiftRightOperation(accValue));
}

/*
ROL - Rotate one bit left (memory or accumulator)

             +------------------------------+
             |         M or A               |
             |   +-+-+-+-+-+-+-+-+    +-+   |
Operation:   +-< |7|6|5|4|3|2|1|0| <- |C| <-+         N Z C I D V
                 +-+-+-+-+-+-+-+-+    +-+             / / / _ _ _
                               (Ref: 10.3)
*/
void Instruction::ROL_Memory(uint16_t memoryAddress) {
  uint8_t memoryValue = busController.read(memoryAddress);
  // Get out current carry value to set the first bit of our value
  bool carryBeforeRotation =
      registerController.getStatusRegister()->getStatus(Carry);
  uint8_t result = alu.shiftLeftOperation(memoryValue) | carryBeforeRotation;

  // Calculating the flags again, because otherwise the negative flag is false
  registerController.getStatusRegister()->setValue(result, 0);

  // Get our last bit before the shift and set the carry according to it
  // The last bit is now the carry value, and we rotated the value
  registerController.getStatusRegister()->setStatus(
      Carry, (memoryValue & 0x80) == 0x80);
  busController.write(memoryAddress, result);
}

void Instruction::ROL_Accumulator() { // TODO Refine
  uint8_t accValue = registerController.getRegisterValue(A);
  // Get out current carry value to set the first bit of our value
  bool carryBeforeRotation =
      registerController.getStatusRegister()->getStatus(Carry);
  uint8_t result = alu.shiftLeftOperation(accValue) | carryBeforeRotation;

  // Calculating the flags again, because otherwise the negative flag is false
  registerController.getStatusRegister()->setValue(result, 0);

  // Get our last bit before the shift and set the carry according to it
  // The last bit is now the carry value, and we rotated the value
  registerController.getStatusRegister()->setStatus(Carry,
                                                    (accValue & 0x80) == 0x80);
  registerController.setRegisterValue(A, accValue);
}

/*
ROR - Rotate one bit right (memory or accumulator)

             +------------------------------+
             |                              |
             |   +-+    +-+-+-+-+-+-+-+-+   |
Operation:   +-> |C| -> |7|6|5|4|3|2|1|0| >-+         N Z C I D V
                 +-+    +-+-+-+-+-+-+-+-+             / / / _ _ _
                              (Ref: 10.4)
*/
void Instruction::ROR_Memory(uint16_t memoryAddress) {
  uint8_t memoryValue = busController.read(memoryAddress);
  // Get out current carry value to set the last bit of our value
  bool carryBeforeRotation =
      registerController.getStatusRegister()->getStatus(Carry);
  uint8_t result =
      alu.shiftRightOperation(memoryValue) | (carryBeforeRotation << 0x7);

  // Calculating the flags again, because otherwise the negative flag is false
  registerController.getStatusRegister()->setValue(result, 0);

  // Get our first bit before the shift and set the carry according to it
  // The first bit is now the carry value, and we rotated the value
  registerController.getStatusRegister()->setStatus(Carry,
                                                    (memoryValue & 0x1) == 0x1);
  busController.write(memoryAddress, result);
}

void Instruction::ROR_Accumulator() { // TODO Summarize with other method
  uint8_t accValue = registerController.getRegisterValue(A);
  // Get out current carry value to set the last bit of our value
  bool carryBeforeRotation =
      registerController.getStatusRegister()->getStatus(Carry);
  uint8_t result =
      alu.shiftRightOperation(accValue) | (carryBeforeRotation << 0x7);

  // Calculating the flags again, because otherwise the negative flag is false
  registerController.getStatusRegister()->setValue(result, 0);

  // Get our first bit before the shift and set the carry according to it
  // The first bit is now the carry value, and we rotated the value
  registerController.getStatusRegister()->setStatus(Carry,
                                                    (accValue & 0x1) == 0x1);
  registerController.setRegisterValue(A, accValue);
}

/*
SBC - Subtract memory from accumulator with borrow

Operation:  A - M - C -> A   N Z C I D V
                             / / / _ _ /
*/
void Instruction::SBC(uint8_t value) {
  uint8_t aValue = registerController.getRegisterValue(A);
  uint8_t result = alu.subOperation(aValue, value);
  registerController.setRegisterValue(A, result);
}

/*
JMP - Jump to new location

Operation:  (PC + 1) -> PCL                           N Z C I D V
            (PC + 2) -> PCH   (Ref: 4.0.2)            _ _ _ _ _ _
                              (Ref: 9.8.1)
*/
void Instruction::JMP(uint16_t memoryAddress) {
  // Setting the program counter minus one
  // because of the increment offset in the decode class
  registerController.setProgramCounter(memoryAddress - 1);
}

void Instruction::branchConditional(Flag flag, bool condition,
                                    int8_t jumpAddress) {
  // If the flag meets the condition just do a jump
  if (registerController.getStatusRegister()->getStatus(flag) == condition) {
    // Calculate the goto jump and calculate the offset
    uint16_t newProgramCounter =
        (registerController.getProgramCounter() - 1) + jumpAddress;
    JMP(newProgramCounter + 2);
  }
}

/*
BCC - Branch on Carry Clear
                                                      N Z C I D V
Operation:  Branch on C = 0                           _ _ _ _ _ _
                               (Ref: 4.1.1.3)
*/
void Instruction::BCC(uint16_t memoryAddress) {
  branchConditional(Carry, false, memoryAddress);
}

/*
BCS - Branch on carry set

Operation:  Branch on C = 1                           N Z C I D V
                                                      _ _ _ _ _ _
                               (Ref: 4.1.1.4)
*/
void Instruction::BCS(uint16_t memoryAddress) {
  branchConditional(Carry, true, memoryAddress);
}

/*
BEQ - Branch on result zero
                                                      N Z C I D V
Operation:  Branch on Z = 1                           _ _ _ _ _ _
                               (Ref: 4.1.1.5)
*/
void Instruction::BEQ(uint16_t memoryAddress) {
  branchConditional(Zero, true, memoryAddress);
}

/*
BMI - Branch on result minus

Operation:  Branch on N = 1                           N Z C I D V
                                                      _ _ _ _ _ _
                               (Ref: 4.1.1.1)
*/
void Instruction::BMI(uint16_t memoryAddress) {
  branchConditional(Negative, true, memoryAddress);
}

/*
BNE - Branch on result not zero

Operation:  Branch on Z = 0                           N Z C I D V
                                                      _ _ _ _ _ _
                               (Ref: 4.1.1.6)
*/
void Instruction::BNE(uint16_t memoryAddress) {
  branchConditional(Zero, false, memoryAddress);
}

/*
BPL - Branch on result plus

Operation:  Branch on N = 0                           N Z C I D V
                                                      _ _ _ _ _ _
                               (Ref: 4.1.1.2)
*/
void Instruction::BPL(uint16_t memoryAddress) {
  branchConditional(Negative, false, memoryAddress);
}

/*
BVC - Branch on overflow clear

Operation:  Branch on V = 0                           N Z C I D V
                                                      _ _ _ _ _ _
                               (Ref: 4.1.1.8)
*/
void Instruction::BVC(uint16_t memoryAddress) {
  branchConditional(Overflow, false, memoryAddress);
}

/*
BVS - Branch on overflow set

Operation:  Branch on V = 1                           N Z C I D V
                                                      _ _ _ _ _ _
                               (Ref: 4.1.1.7)
*/
void Instruction::BVS(uint16_t memoryAddress) {
  branchConditional(Overflow, true, memoryAddress);
}

/*
CMP - Compare memory and accumulator

Operation:  A - M                                     N Z C I D V
                                                      / / / _ _ _
                                (Ref: 4.2.1)
*/
void Instruction::CMP(uint16_t memoryAddress) {
  uint8_t aValue = registerController.getRegisterValue(A);
  bool carry = registerController.getStatusRegister()->getStatus(Carry);
  bool overflow = registerController.getStatusRegister()->getStatus(Overflow);
  alu.subOperation(aValue, memoryAddress);
  registerController.getStatusRegister()->setStatus(Overflow, overflow);
}

/*
CPX - Compare Memory and Index X
                                                      N Z C I D V
Operation:  X - M                                     / / / _ _ _
                                 (Ref: 7.8)
*/
void Instruction::CPX(
    uint16_t memoryAddress) { // TODO FIX DATATYPE IN ALL CP INSTRUCT
  bool overflow = registerController.getStatusRegister()->getStatus(Overflow);
  uint8_t xValue = registerController.getRegisterValue(X);
  alu.subOperation(xValue, memoryAddress);
  registerController.getStatusRegister()->setStatus(Overflow, overflow);
}

/*
CPY - Compare memory and index Y
                                                      N Z C I D V
Operation:  Y - M                                     / / / _ _ _
                                 (Ref: 7.9)
*/
void Instruction::CPY(uint16_t memoryAddress) {
  bool overflow = registerController.getStatusRegister()->getStatus(Overflow);
  uint8_t yValue = registerController.getRegisterValue(Y);
  alu.subOperation(yValue, memoryAddress); // TODO CHECK LINE0x57e
  registerController.getStatusRegister()->setStatus(Overflow, overflow);
}

/*
  BIT             BIT Test bits in memory with accumulator              BIT

  Operation:  A /\ M, M7 -> N, M6 -> V

  Bit 6 and 7 are transferred to the status register.   N Z C I D V
  If the result of A /\ M is zero then Z = 1, otherwise M7/ _ _ _ M6
  Z = 0
                               (Ref: 4.2.1.1)
*/
void Instruction::BIT(uint16_t memoryAddress) {
  uint8_t aValue = registerController.getRegisterValue(A);
  uint8_t memory = busController.read(memoryAddress);
  alu.andOperation(aValue, memory);
  registerController.getStatusRegister()->setStatus(Negative, memory >> 7);
  registerController.getStatusRegister()->setStatus(Overflow,
                                                    (memory >> 6) & 0x1);
}

/*
JSR - Jump to new location saving return address

Operation:  PC + 2 toS, (PC + 1) -> PCL               N Z C I D V
                          (PC + 2) -> PCH             _ _ _ _ _ _
                                 (Ref: 8.1)
*/
void Instruction::JSR(uint16_t memoryAddress) {
  // TODO Check length needed
  registerController.getStack()->pushWord(
      registerController.getProgramCounter());
  JMP(memoryAddress);
}

/*
BRK - Force Break

Operation: Forced Interrupt PC + 2 toS P toS         N Z C I D V
                                                     _ _ _ 1 _ _
*/
void Instruction::BRK() {
  registerController.getStatusRegister()->setStatus(BreakSignal, true);
}

/*
RTS - Return from subroutine
                                                      N Z C I D V
Operation:  PC fromS, PC + 1 -> PC                    _ _ _ _ _ _
                                 (Ref: 8.2)
*/
void Instruction::RTS() {
  registerController.setProgramCounter(
      registerController.getStack()->pullWord());
}