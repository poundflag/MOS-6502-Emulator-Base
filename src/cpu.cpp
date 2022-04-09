#include "cpu.h"

CPU::CPU() {
  alu = new ALU(registerController);
  instruction = new Instruction(registerController, busController, *alu);
  instructionDecodeRom =
      new InstructionDecodeRom(*instruction, registerController, busController);
  resetCPU = true;
}

uint8_t CPU::fetch() {
  // If this is the first fetch then run the init. first
  if (resetCPU) {
    fetchResetVector();
    resetCPU = false;
  }
  return busController.read(registerController.getProgramCounter());
}

void CPU::step(int steps) {
  bool lBreak = false;
  for (int i = 0; i < steps && !lBreak; i++) {
    lBreak = instructionDecodeRom->decodeOpcode(fetch());
    registerController.incrementProgramCounter();
  }
}

void CPU::run() {}

BusController &CPU::getBusController() { return busController; }

// Fetch memory content in address $FFFC and $FFFD
// on reset or power-up
void CPU::fetchResetVector() {
  registerController.setRegisterValue(PCL, busController.read(RESET_VECTOR));
  registerController.setRegisterValue(PCH,
                                      busController.read(RESET_VECTOR + 1));
}

CPU::~CPU() {
  delete alu;
  delete instruction;
  delete instructionDecodeRom;
}
