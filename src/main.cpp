#include "cpu.h"
#include <iostream>

int main() {
  std::cout << "Hello";
  CPU cpu = CPU();

  cpu.getBusController().addRamChip(
      "/Users/robin/Documents/GitHub/MOS-6502-Emulator-Base/rom/"
      "6502_functional_test.bin");

  cpu.step(1);

  cpu.getRegisterController().setProgramCounter(0x400);

  cpu.step(40916);
  if (cpu.getRegisterController().getStatusRegister()->getStatus(BreakSignal) && cpu.getRegisterController().getProgramCounter() == 0x09D0) {
    std::cout << "Success";
  }
}