#include "instructiondecoderom.h"

InstructionDecodeRom::InstructionDecodeRom(
    Instruction &instruction, RegisterController &registerController,
    BusController &busController)
    : instruction{instruction}, registerController{registerController} {
  addressConvert = new AddressModeConversion(registerController, busController);
}

void InstructionDecodeRom::decodeOpcode(uint8_t opcode) {
  switch (opcode) {
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
