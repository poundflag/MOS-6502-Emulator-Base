#include "instructiondecoderom.h"
#include <bitset>

InstructionDecodeRom::InstructionDecodeRom(
    Instruction &instruction, RegisterController &registerController,
    BusController &busController)
    : instruction{instruction}, registerController{registerController} {
  addressConvert = new AddressModeConversion(registerController, busController);
}

bool InstructionDecodeRom::decodeOpcode(uint8_t opcode) {
  switch (opcode) { // TODO Does TSX Change flags???
  case 0x00:
    instruction.BRK();
    return true;
    break;
  case 0x20:
    instruction.JSR(getNextWord());
    break;
  case 0x40:
    // TODO instruction.RTI();
    break;
  case 0x60:
    instruction.RTS();
    break;
  case 0x08:
    instruction.PHP();
    break;
  case 0x18:
    instruction.CLC();
    break;
  case 0x28:
    instruction.PLP();
    break;
  case 0x38:
    instruction.SEC();
    break;
  case 0x48:
    instruction.PHA();
    break;
  case 0x58:
    instruction.CLI();
    break;
  case 0x68:
    instruction.PLA();
    break;
  case 0x78:
    instruction.SEI();
    break;
  case 0x88:
    instruction.DEY();
    break;
  case 0x98:
    instruction.TYA();
    break;
  case 0xA8:
    instruction.TAY();
    break;
  case 0xB8:
    instruction.CLV();
    break;
  case 0xC8:
    instruction.INY();
    break;
  case 0xD8:
    instruction.CLD();
    break;
  case 0xE8:
    instruction.INX();
    break;
  case 0xF8:
    instruction.SED();
    break;
  case 0x8A:
    instruction.TXA();
    break;
  case 0x9A:
    instruction.TXS();
    break;
  case 0xAA:
    instruction.TAX();
    break;
  case 0xBA:
    instruction.TSX();
    break;
  case 0xCA:
    instruction.DEX();
    break;
  case 0xEA:
    break;

    // Branch Instructions
  case 0x10:
    instruction.BPL(getNextByte());
    break;
  case 0xF0:
    instruction.BEQ(getNextByte());
    break;
  case 0xD0:
    instruction.BNE(getNextByte());
    break;
  case 0xB0:
    instruction.BCS(getNextByte());
    break;
  case 0x30:
    instruction.BMI(getNextByte());
    break;
  case 0x70:
    instruction.BVS(getNextByte());
    break;
  case 0x90:
    instruction.BCC(getNextByte());
    break;
  case 0x50:
    instruction.BVC(getNextByte());
    break;

    // BIT Instructions
  case 0x24:
    instruction.BIT(addressConvert->zeroPage(getNextByte()));
    break;
  case 0x2C:
    instruction.BIT(addressConvert->absolute(getNextWord()));
    break;

    // JMP Instructions
  case 0x4C:
    instruction.JMP(getNextWord());
    break;
  case 0x6C:
    instruction.JMP(addressConvert->absoluteIndirect(getNextWord()));
    break;

    // STY Instructions
  case 0x84:
    instruction.STY(addressConvert->zeroPage(getNextByte()));
    break;
  case 0x94:
    instruction.STY(addressConvert->zeroPageXIndexed(getNextByte()));
    break;
  case 0x8C:
    instruction.STY(addressConvert->absolute(getNextWord()));
    break;

    // LDY Instructions
  case 0xA0:
    instruction.LDY(getNextByte());
    break;
  case 0xA4:
    instruction.LDY(addressConvert->zeroPage(getNextByte()));
    break;
  case 0xB4:
    instruction.LDY(addressConvert->zeroPageXIndexed(getNextByte()));
    break;
  case 0xAC:
    instruction.LDY(addressConvert->absolute(getNextWord()));
    break;
  case 0xBC:
    instruction.LDY(addressConvert->absoluteXIndexed(getNextWord()));
    break;

    // CPY Instructions
  case 0xCC:
    instruction.CPY(addressConvert->absolute(getNextWord()));
    break;
  case 0xC0:
    instruction.CPY(getNextByte());
    break;
  case 0xC4:
    instruction.CPY(addressConvert->zeroPage(getNextByte()));
    break;

    // CPX Instructions
  case 0xEC:
    instruction.CPX(addressConvert->absolute(getNextWord()));
    break;
  case 0xE4:
    instruction.CPX(addressConvert->zeroPage(getNextByte()));
    break;
  case 0xE0:
    instruction.CPX(getNextByte());
    break;

    // ORA Instructions
  case 0x01:
    instruction.ORA(addressConvert->indexedIndirect(getNextByte()));
    break;
  case 0x11:
    instruction.ORA(addressConvert->indirectIndexed(getNextByte()));
    break;
  case 0x09:
    instruction.ORA(getNextByte());
    break;
  case 0x19:
    instruction.ORA(addressConvert->absoluteYIndexed(getNextWord()));
    break;
  case 0x05:
    instruction.ORA(addressConvert->zeroPage(getNextByte()));
    break;
  case 0x15:
    instruction.ORA(addressConvert->zeroPageXIndexed(getNextByte()));
    break;
  case 0x0D:
    instruction.ORA(addressConvert->absolute(getNextWord()));
    break;
  case 0x1D:
    instruction.ORA(addressConvert->absoluteXIndexed(getNextWord()));
    break;

    // AND Instructions
  case 0x21:
    instruction.AND(addressConvert->indexedIndirect(getNextByte()));
    break;
  case 0x31:
    instruction.AND(addressConvert->indirectIndexed(getNextByte()));
    break;
  case 0x25:
    instruction.AND(addressConvert->zeroPage(getNextByte()));
    break;
  case 0x35:
    instruction.AND(addressConvert->zeroPageXIndexed(getNextByte()));
    break;
  case 0x29:
    instruction.AND(getNextByte());
    break;
  case 0x39:
    instruction.AND(addressConvert->absoluteYIndexed(getNextWord()));
    break;
  case 0x2D:
    instruction.AND(addressConvert->absolute(getNextWord()));
    break;
  case 0x3D:
    instruction.AND(addressConvert->absoluteXIndexed(getNextWord()));
    break;

    // EOR Instructions
  case 0x41:
    instruction.EOR(addressConvert->indexedIndirect(getNextByte()));
    break;
  case 0x51:
    instruction.EOR(addressConvert->indirectIndexed(getNextByte()));
    break;
  case 0x45:
    instruction.EOR(addressConvert->zeroPage(getNextByte()));
    break;
  case 0x55:
    instruction.EOR(addressConvert->zeroPageXIndexed(getNextByte()));
    break;
  case 0x49:
    instruction.EOR(getNextByte());
    break;
  case 0x59:
    instruction.EOR(addressConvert->absoluteYIndexed(getNextWord()));
    break;
  case 0x4D:
    instruction.EOR(addressConvert->absolute(getNextWord()));
    break;
  case 0x5D:
    instruction.EOR(addressConvert->absoluteXIndexed(getNextWord()));
    break;

    // ADC Instructions
  case 0x61:
    instruction.ADC(addressConvert->indexedIndirect(getNextByte()));
    break;
  case 0x71:
    instruction.ADC(addressConvert->indirectIndexed(getNextByte()));
    break;
  case 0x65:
    instruction.ADC(addressConvert->zeroPage(getNextByte()));
    break;
  case 0x75:
    instruction.ADC(addressConvert->zeroPageXIndexed(getNextByte()));
    break;
  case 0x69:
    instruction.ADC(getNextByte());
    break;
  case 0x79:
    instruction.ADC(addressConvert->absoluteYIndexed(getNextWord()));
    break;
  case 0x6D:
    instruction.ADC(addressConvert->absolute(getNextWord()));
    break;
  case 0x7D:
    instruction.ADC(addressConvert->absoluteXIndexed(getNextWord()));
    break;

    // STA Instructions
  case 0x99:
    instruction.STA(addressConvert->absoluteYIndexed(getNextWord()));
    break;
  case 0x81:
    instruction.STA(addressConvert->indexedIndirect(getNextByte()));
    break;
  case 0x91:
    instruction.STA(addressConvert->indirectIndexed(getNextByte()));
    break;
  case 0x85:
    instruction.STA(addressConvert->zeroPage(getNextByte()));
    break;
  case 0x95:
    instruction.STA(addressConvert->zeroPageXIndexed(getNextByte()));
    break;
  case 0x8D:
    instruction.STA(getNextWord());
    break;
  case 0x9D:
    instruction.STA(addressConvert->absoluteXIndexed(getNextWord()));
    break;

    // LDA Instructions
  case 0xA1:
    instruction.LDA(addressConvert->indexedIndirect(getNextByte()));
    break;
  case 0xB1:
    instruction.LDA(addressConvert->indirectIndexed(getNextByte()));
    break;
  case 0xA5:
    instruction.LDA(addressConvert->zeroPage(getNextByte()));
    break;
  case 0xB5:
    instruction.LDA(addressConvert->zeroPageXIndexed(getNextByte()));
    break;
  case 0xA9:
    instruction.LDA(getNextByte());
    break;
  case 0xB9:
    instruction.LDA(addressConvert->absoluteYIndexed(getNextWord()));
    break;
  case 0xAD:
    instruction.LDA(addressConvert->absolute(getNextWord()));
    break;
  case 0xBD:
    instruction.LDA(addressConvert->absoluteXIndexed(getNextWord()));
    break;

    // CMP Instructions
  case 0xC1:
    instruction.CMP(addressConvert->indexedIndirect(getNextByte()));
    break;
  case 0xC5:
    instruction.CMP(addressConvert->zeroPage(getNextByte()));
    break;
  case 0xC9:
    instruction.CMP(getNextByte());
    break;
  case 0xCD:
    instruction.CMP(addressConvert->absolute(getNextWord()));
    break;
  case 0xD1:
    instruction.CMP(addressConvert->indirectIndexed(getNextByte()));
    break;
  case 0xD5:
    instruction.CMP(addressConvert->zeroPageXIndexed(getNextByte()));
    break;
  case 0xD9:
    instruction.CMP(addressConvert->absoluteYIndexed(getNextWord()));
    break;
  case 0xDD:
    instruction.CMP(addressConvert->absoluteXIndexed(getNextWord()));
    break;

    // SBC Instructions
  case 0xE1:
    instruction.SBC(addressConvert->indexedIndirect(getNextByte()));
    break;
  case 0xF1:
    instruction.SBC(addressConvert->indirectIndexed(getNextByte()));
    break;
  case 0xE5:
    instruction.SBC(addressConvert->zeroPage(getNextByte()));
    break;
  case 0xF5:
    instruction.SBC(addressConvert->zeroPageXIndexed(getNextByte()));
    break;
  case 0xE9:
    instruction.SBC(getNextByte());
    break;
  case 0xF9:
    instruction.SBC(addressConvert->absoluteYIndexed(getNextWord()));
    break;
  case 0xED:
    instruction.SBC(addressConvert->absolute(getNextWord()));
    break;
  case 0xFD:
    instruction.SBC(addressConvert->absoluteXIndexed(getNextWord()));
    break;

    // ASL Instructions
  case 0x0A:
    instruction.ASL_Accumulator();
    break;
  case 0x06:
    instruction.ASL_Memory(addressConvert->zeroPage(getNextByte()));
    break;
  case 0x16:
    instruction.ASL_Memory(addressConvert->zeroPageXIndexed(getNextByte()));
    break;
  case 0x0E:
    instruction.ASL_Memory(addressConvert->absolute(getNextWord()));
    break;
  case 0x1E:
    instruction.ASL_Memory(addressConvert->absoluteXIndexed(getNextWord()));
    break;

    // ROL Instructions
  case 0x26:
    instruction.ROL_Memory(addressConvert->zeroPage(getNextByte()));
    break;
  case 0x36:
    instruction.ROL_Memory(addressConvert->zeroPageXIndexed(getNextByte()));
    break;
  case 0x2A:
    instruction.ROL_Accumulator();
    break;
  case 0x2E:
    instruction.ROL_Memory(addressConvert->absolute(getNextWord()));
    break;
  case 0x3E:
    instruction.ROL_Memory(addressConvert->absoluteXIndexed(getNextWord()));
    break;

    // LSR Instructions
  case 0x46:
    instruction.LSR_Memory(addressConvert->zeroPage(getNextByte()));
    break;
  case 0x56:
    instruction.LSR_Memory(addressConvert->zeroPageXIndexed(getNextByte()));
    break;
  case 0x4A:
    instruction.LSR_Accumulator();
    break;
  case 0x4E:
    instruction.LSR_Memory(addressConvert->absolute(getNextWord()));
    break;
  case 0x5E:
    instruction.LSR_Memory(addressConvert->absoluteXIndexed(getNextWord()));
    break;

    // ROR Instructions
  case 0x66:
    instruction.ROR_Memory(addressConvert->zeroPage(getNextByte()));
    break;
  case 0x76:
    instruction.ROR_Memory(addressConvert->zeroPageXIndexed(getNextByte()));
    break;
  case 0x6A:
    instruction.ROR_Accumulator();
    break;
  case 0x6E:
    instruction.ROR_Memory(addressConvert->absolute(getNextWord()));
    break;
  case 0x7E:
    instruction.ROR_Memory(addressConvert->absoluteXIndexed(getNextWord()));
    break;

    // STX Instructions
  case 0x86:
    instruction.STX(addressConvert->zeroPage(getNextByte()));
    break;
  case 0x96:
    instruction.STX(addressConvert->zeroPageYIndexed(getNextByte()));
    break;
  case 0x8E:
    instruction.STX(addressConvert->absolute(getNextWord()));
    break;

    // LDX Instructions
  case 0xA2:
    instruction.LDX(getNextByte());
    break;
  case 0xA6:
    instruction.LDX(addressConvert->zeroPage(getNextByte()));
    break;
  case 0xB6:
    instruction.LDX(addressConvert->zeroPageYIndexed(getNextByte()));
    break;
  case 0xAE:
    instruction.LDX(addressConvert->absolute(getNextWord()));
    break;
  case 0xBE:
    instruction.LDX(addressConvert->absoluteYIndexed(getNextWord()));
    break;

    // DEC Instructions
  case 0xC6:
    instruction.DEC(addressConvert->zeroPage(getNextByte()));
    break;
  case 0xD6:
    instruction.DEC(addressConvert->zeroPageXIndexed(getNextByte()));
    break;
  case 0xCE:
    instruction.DEC(addressConvert->absolute(getNextWord()));
    break;
  case 0xDE:
    instruction.DEC(addressConvert->absoluteXIndexed(getNextWord()));
    break;

    // INC Instructions
  case 0xE6:
    instruction.INC(addressConvert->zeroPage(getNextByte()));
    break;
  case 0xF6:
    instruction.INC(addressConvert->zeroPageXIndexed(getNextByte()));
    break;
  case 0xEE:
    instruction.INC(addressConvert->absolute(getNextWord()));
    break;
  case 0xFE:
    instruction.INC(addressConvert->absoluteXIndexed(getNextWord()));
    break;
  }

  /*std::cout << "A:" << registerController.getRegisterValue(A)
            << " X:" << registerController.getRegisterValue(X)
            << " Y:" << registerController.getRegisterValue(Y)
            << " SP: " << registerController.getStack()->getValue()
            << " St:"
            << std::bitset<8>(
                   registerController.getStatusRegister()->getValue())
                   .to_string()
            << std::endl;*/

  // return registerController.getStatusRegister()->getStatus(BreakSignal);
  return false;
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

uint8_t InstructionDecodeRom::getNextByte() { // TODO Refine
  registerController.incrementProgramCounter();
  uint8_t ADL =
      addressConvert->absolute(registerController.getProgramCounter());
  return ADL;
}

InstructionDecodeRom::~InstructionDecodeRom() { delete addressConvert; }
