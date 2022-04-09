#include "instruction.h"
#include "../bus/buscontroller.h"
#include "../register/registercontroller.h"
#include "addressmodeconversion.h"
#include <stdint.h>

#ifndef __INSTRUCTIONDECODEROM_H__
#define __INSTRUCTIONDECODEROM_H__

class InstructionDecodeRom {
private:
  Instruction instruction;
  AddressModeConversion *addressConvert;
  RegisterController &registerController;

public:
  InstructionDecodeRom(Instruction &instruction,
                       RegisterController &registerController,
                       BusController &busController);
  bool decodeOpcode(uint8_t opcode);
  uint16_t getNextWord();
  uint8_t getNextByte();
  ~InstructionDecodeRom();
};

#endif // __INSTRUCTIONDECODEROM_H__