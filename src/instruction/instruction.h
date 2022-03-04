#include "../bus/buscontroller.h"
#include "../register/registercontroller.h"
#include <stdint.h>

#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

class Instruction {
private:
  RegisterController &registerController;
  BusController &busController;

public:
  Instruction(RegisterController &registerController,
              BusController &busController);
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
};

#endif // __INSTRUCTION_H__