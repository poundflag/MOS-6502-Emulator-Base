#include "alu.h"
#include "bus/buscontroller.h"
#include "instruction/instruction.h"
#include "instruction/instructiondecoderom.h"
#include "register/registercontroller.h"

#ifndef __CPU_H__
#define __CPU_H__

const int RESET_VECTOR = 0xFFFC;

class CPU {
private:
  BusController busController = BusController();
  RegisterController registerController = RegisterController(busController);
  Instruction *instruction;
  InstructionDecodeRom *instructionDecodeRom;
  ALU *alu;
  bool resetCPU;

  void fetchResetVector();

public:
  CPU();
  uint8_t fetch();
  void step(int steps);
  void run();
  ~CPU();
};

#endif // __CPU_H__