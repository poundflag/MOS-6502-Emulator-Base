#include "../src/bus/model/ramdebug.h"
#include "../src/cpu.h"
#include <gtest/gtest.h>

class IntegrationTest : public ::testing::Test {
protected:
  CPU cpu = CPU();

  void SetUp() {

    cpu.getBusController().addRamChip(
        "/Users/robin/Documents/GitHub/MOS-6502-Emulator-Base/rom/"
        "6502_functional_test.bin");
  }
};

TEST_F(IntegrationTest, testRom) {

  cpu.step(1);

  cpu.getRegisterController().setProgramCounter(0x400);
  cpu.step(40916);
  GTEST_ASSERT_TRUE(
      cpu.getRegisterController().getStatusRegister()->getStatus(BreakSignal) &&
      cpu.getRegisterController().getProgramCounter() == 0x09D0);
}