#include "instructiondecoderom.h"

InstructionDecodeRom::InstructionDecodeRom(
    Instruction &instruction, RegisterController &registerController,
    BusController &busController)
    : instruction{instruction}, registerController{registerController} {
  addressConvert = new AddressModeConversion(registerController, busController);
}

void InstructionDecodeRom::decodeOpcode(uint8_t opcode) {
  switch (opcode) {
  case 0x2C:
    instruction.BIT(addressConvert->absolute(getNextWord()));
    break;
  case 0x4C:
    instruction.JMP(addressConvert->absolute(getNextWord()));
    break;
  case 0x6C:
    instruction.JMP(addressConvert->absoluteIndirect(getNextWord()));
    break;
  case 0x8C:
    instruction.STY(addressConvert->absolute(getNextWord()));
    break;
  case 0xAC:
    instruction.LDY(addressConvert->absolute(getNextWord()));
    break;
  case 0xBC:
    instruction.LDY(addressConvert->absoluteXIndexed(getNextWord()));
    break;
  case 0xCC:
    instruction.CPY(addressConvert->absolute(getNextWord()));
    break;
  case 0xEC:
    instruction.CPX(addressConvert->absolute(getNextWord()));
    break;
  case 0x0D:
    instruction.ORA(addressConvert->absolute(getNextWord()));
    break;
  case 0x1D:
    instruction.ORA(addressConvert->absoluteXIndexed(getNextWord()));
    break;
  case 0x2D:
    instruction.AND(addressConvert->absolute(getNextWord()));
    break;
  case 0x3D:
    instruction.AND(addressConvert->absoluteXIndexed(getNextWord()));
    break;
  case 0x4D:
    instruction.EOR(addressConvert->absolute(getNextWord()));
    break;
  case 0x5D:
    instruction.EOR(addressConvert->absoluteXIndexed(getNextWord()));
    break;
  case 0x6D:
    instruction.ADC(addressConvert->absolute(getNextWord()));
    break;
  case 0x7D:
    instruction.ADC(addressConvert->absoluteXIndexed(getNextWord()));
    break;
  case 0x8D:
    instruction.STA(addressConvert->absolute(getNextWord()));
    break;
  case 0x9D:
    instruction.STA(addressConvert->absoluteXIndexed(getNextWord()));
    break;
  case 0xAD:
    instruction.LDA(addressConvert->absolute(getNextWord()));
    break;
  case 0xBD:
    instruction.LDA(addressConvert->absoluteXIndexed(getNextWord()));
    break;
  case 0xCD:
    instruction.CMP(addressConvert->absolute(getNextWord()));
    break;
  case 0xDD:
    instruction.CMP(addressConvert->absoluteXIndexed(getNextWord()));
    break;
  case 0xED:
    instruction.SBC(addressConvert->absolute(getNextWord()));
    break;
  case 0xFD:
    instruction.SBC(addressConvert->absoluteXIndexed(getNextWord()));
    break;
  case 0x0E:
    instruction.ASL_Memory(addressConvert->absolute(getNextWord()));
    break;
  case 0x1E:
    instruction.ASL_Memory(addressConvert->absoluteXIndexed(getNextWord()));
    break;
  case 0x2E:
    instruction.ROL_Memory(addressConvert->absolute(getNextWord()));
    break;
  case 0x3E:
    instruction.ROL_Memory(addressConvert->absoluteXIndexed(getNextWord()));
    break;
  case 0x4E:
    instruction.LSR_Memory(addressConvert->absolute(getNextWord()));
    break;
  case 0x5E:
    instruction.LSR_Memory(addressConvert->absoluteXIndexed(getNextWord()));
    break;
  case 0x6E:
    instruction.ROR_Memory(addressConvert->absolute(getNextWord()));
    break;
  case 0x7E:
    instruction.ROR_Memory(addressConvert->absoluteXIndexed(getNextWord()));
    break;
  case 0x8E:
    instruction.STX(addressConvert->absolute(getNextWord()));
    break;
  case 0xAE:
    instruction.LDX(addressConvert->absolute(getNextWord()));
    break;
  case 0xBE:
    instruction.LDX(addressConvert->absoluteYIndexed(getNextWord()));
    break;
  case 0xCE:
    instruction.DEC(addressConvert->absolute(getNextWord()));
    break;
  case 0xDE:
    instruction.DEC(addressConvert->absoluteXIndexed(getNextWord()));
    break;
  case 0xEE:
    instruction.INC(addressConvert->absolute(getNextWord()));
    break;
  case 0xFE:
    instruction.INC(addressConvert->absoluteXIndexed(getNextWord()));
    break;
  }
}

uint16_t InstructionDecodeRom::getNextWord() {
  registerController.incrementProgramCounter();
  uint8_t ADL =
      addressConvert->absolute(registerController.getProgramCounter());
  registerController.incrementProgramCounter();
  uint8_t ADH =
      addressConvert->absolute(registerController.getProgramCounter());
  return (ADH << 8) + ADL;
}

InstructionDecodeRom::~InstructionDecodeRom() { delete addressConvert; }
