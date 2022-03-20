#include "../alu.h"
#include "../bus/buscontroller.h"
#include "../register/registercontroller.h"
#include <stdint.h>

#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

class Instruction { // TODO Move files to root dir.s
private:
  RegisterController &registerController;
  BusController &busController;
  ALU &alu;
  void branchConditional(Flag flag, bool condition, uint16_t jumpAddress);

public:
  Instruction(RegisterController &registerController,
              BusController &busController, ALU &alu);
  uint8_t absolute(uint16_t address);
  void LDA(uint8_t value);
  void LDX(uint8_t value);
  void LDY(uint8_t value);
  void STA(uint16_t address);
  void STX(uint16_t address);
  void STY(uint16_t address);
  void CLC();
  void CLD();
  void CLI();
  void CLV();
  void SEC();
  void SED();
  void SEI();
  void DEC(uint16_t address);
  void DEX();
  void DEY();
  void INC(uint16_t address);
  void INX();
  void INY();
  void AND(uint16_t address);
  void EOR(uint16_t address);
  void ORA(uint16_t address);
  void TAX();
  void TAY();
  void TSX();
  void TXA();
  void TXS();
  void TYA();
  void PHA();
  void PHP();
  void PLA();
  void PLP();
  void ADC(uint8_t value);
  void ASL_Memory(uint16_t memoryAddress);
  void LSR_Memory(uint16_t memoryAddress); // TODO Implement acc call
  void ROL_Memory(uint16_t memoryAddress);
  void ROR_Memory(uint16_t memoryAddress);
  void SBC(uint8_t value);
  void JMP(uint16_t memoryAddress);
  void BCC(uint16_t memoryAddress);
  void BCS(uint16_t memoryAddress);
  void BEQ(uint16_t memoryAddress);
  void BMI(uint16_t memoryAddress);
  void BNE(uint16_t memoryAddress);
  void BPL(uint16_t memoryAddress);
  void BVC(uint16_t memoryAddress);
  void BVS(uint16_t memoryAddress);
  void CMP(uint16_t memoryAddress);
  void CPX(uint16_t memoryAddress);
  void CPY(uint16_t memoryAddress);
  void BIT(uint16_t memoryAddress);
  void JSR(uint16_t memoryAddress);
  void RTS();
};

#endif // __INSTRUCTION_H__