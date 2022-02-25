#include "../../src/instruction/instruction.h"
#include "../../src/bus/buscontroller.h"
#include "../../src/bus/model/busdevice.h"
#include "../../src/bus/model/ram.h"
#include "../../src/register/registercontroller.h"
#include <gtest/gtest.h>

class InstructionTest : public ::testing::Test {
protected:
  BusController busController = BusController();
  Ram *ram = new Ram(0x10);
  RegisterController registerController = RegisterController();
  Instruction instr = Instruction(registerController, busController);
  void SetUp() {
    ram->addAddress({0x0, 0x10});
    busController.addDevice(ram);
  }
};

TEST_F(InstructionTest, LDA) {
  instr.LDA(0x46);
  GTEST_ASSERT_EQ(0x46, registerController.getRegisterValue(A));
}

TEST_F(InstructionTest, LDAWithZeroFlagTrigger) {
  instr.LDA(0x0);
  GTEST_ASSERT_EQ(0x0, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Zero));
}

TEST_F(InstructionTest, LDAWithNegativeFlagTrigger) {
  instr.LDA(0x80);
  GTEST_ASSERT_EQ(0x80, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Negative));
}

TEST_F(InstructionTest, LDX) {
  instr.LDX(0x46);
  GTEST_ASSERT_EQ(0x46, registerController.getRegisterValue(X));
}

TEST_F(InstructionTest, LDXWithZeroFlagTrigger) {
  instr.LDX(0x0);
  GTEST_ASSERT_EQ(0x0, registerController.getRegisterValue(X));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Zero));
}

TEST_F(InstructionTest, LDXWithNegativeFlagTrigger) {
  instr.LDX(0x80);
  GTEST_ASSERT_EQ(0x80, registerController.getRegisterValue(X));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Negative));
}

TEST_F(InstructionTest, LDY) {
  instr.LDY(0x46);
  GTEST_ASSERT_EQ(0x46, registerController.getRegisterValue(Y));
}

TEST_F(InstructionTest, LDYWithZeroFlagTrigger) {
  instr.LDY(0x0);
  GTEST_ASSERT_EQ(0x0, registerController.getRegisterValue(Y));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Zero));
}

TEST_F(InstructionTest, LDYWithNegativeFlagTrigger) {
  instr.LDY(0x80);
  GTEST_ASSERT_EQ(0x80, registerController.getRegisterValue(Y));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Negative));
}

TEST_F(InstructionTest, STA) {
  instr.LDA(0x32);
  instr.STA(0x0);
  GTEST_ASSERT_EQ(0x32, busController.read(0));
}

TEST_F(InstructionTest, STAWithOutOfRangeAddress) {
  instr.LDA(0x35);
  instr.STA(0x1000);
  GTEST_ASSERT_EQ(0x0, busController.read(0x1000));
}

TEST_F(InstructionTest, STX) {
  instr.LDX(0x32);
  instr.STX(0x0);
  GTEST_ASSERT_EQ(0x32, busController.read(0));
}

TEST_F(InstructionTest, STXWithOutOfRangeAddress) {
  instr.LDX(0x35);
  instr.STX(0x1000);
  GTEST_ASSERT_EQ(0x0, busController.read(0x1000));
}

TEST_F(InstructionTest, STY) {
  instr.LDY(0x32);
  instr.STY(0x0);
  GTEST_ASSERT_EQ(0x32, busController.read(0));
}

TEST_F(InstructionTest, STYWithOutOfRangeAddress) {
  instr.LDY(0x35);
  instr.STY(0x1000);
  GTEST_ASSERT_EQ(0x0, busController.read(0x1000));
}

TEST_F(InstructionTest, CLC) {
  registerController.getStatusRegister()->setStatus(Carry, true);
  instr.CLC();
  GTEST_ASSERT_EQ(false,
                  registerController.getStatusRegister()->getStatus(Carry));
}

TEST_F(InstructionTest, CLD) {
  registerController.getStatusRegister()->setStatus(DecimalMode, true);
  instr.CLD();
  GTEST_ASSERT_EQ(
      false, registerController.getStatusRegister()->getStatus(DecimalMode));
}

TEST_F(InstructionTest, CLI) {
  registerController.getStatusRegister()->setStatus(Interrupt, true);
  instr.CLI();
  GTEST_ASSERT_EQ(false,
                  registerController.getStatusRegister()->getStatus(Interrupt));
}

TEST_F(InstructionTest, CLV) {
  registerController.getStatusRegister()->setStatus(Overflow, true);
  instr.CLV();
  GTEST_ASSERT_EQ(false,
                  registerController.getStatusRegister()->getStatus(Overflow));
}

TEST_F(InstructionTest, SEC) {
  registerController.getStatusRegister()->setStatus(Carry, false);
  instr.SEC();
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Carry));
}

TEST_F(InstructionTest, SED) {
  registerController.getStatusRegister()->setStatus(DecimalMode, false);
  instr.SED();
  GTEST_ASSERT_EQ(
      true, registerController.getStatusRegister()->getStatus(DecimalMode));
}

TEST_F(InstructionTest, SEI) {
  registerController.getStatusRegister()->setStatus(Interrupt, false);
  instr.SEI();
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Interrupt));
}

TEST_F(InstructionTest, DECWithNotFlagChanged) {
  busController.write(1, 0x23);
  instr.DEC(1);
  GTEST_ASSERT_EQ(0x22, busController.read(1));
}

TEST_F(InstructionTest, DECZeroFlagAffected) {
  busController.write(1, 0x1);
  instr.DEC(1);
  GTEST_ASSERT_EQ(0x0, busController.read(1));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Zero));
}

TEST_F(InstructionTest, DECNegativeFlagAffected) {
  busController.write(1, 0x0);
  instr.DEC(1);
  GTEST_ASSERT_EQ(0xFF, busController.read(1));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Negative));
}

TEST_F(InstructionTest, DEXWithNotFlagChanged) {
  registerController.setRegisterValue(X, 0x99);
  instr.DEX();
  GTEST_ASSERT_EQ(0x98, registerController.getRegisterValue(X));
}

TEST_F(InstructionTest, DEXZeroFlagAffected) {
  registerController.setRegisterValue(X, 0x1);
  instr.DEX();
  GTEST_ASSERT_EQ(0x0, registerController.getRegisterValue(X));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Zero));
}

TEST_F(InstructionTest, DEXNegativeFlagAffected) {
  registerController.setRegisterValue(X, 0xFF);
  instr.DEX();
  GTEST_ASSERT_EQ(0xFE, registerController.getRegisterValue(X));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Negative));
}

TEST_F(InstructionTest, DEYWithNotFlagChanged) {
  registerController.setRegisterValue(Y, 0x99);
  instr.DEY();
  GTEST_ASSERT_EQ(0x98, registerController.getRegisterValue(Y));
}

TEST_F(InstructionTest, DEYZeroFlagAffected) {
  registerController.setRegisterValue(Y, 0x1);
  instr.DEY();
  GTEST_ASSERT_EQ(0x0, registerController.getRegisterValue(Y));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Zero));
}

TEST_F(InstructionTest, DEYNegativeFlagAffected) {
  registerController.setRegisterValue(Y, 0xFF);
  instr.DEY();
  GTEST_ASSERT_EQ(0xFE, registerController.getRegisterValue(Y));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Negative));
}

TEST_F(InstructionTest, INCWithNotFlagChanged) {
  busController.write(1, 0x23);
  instr.INC(1);
  GTEST_ASSERT_EQ(0x24, busController.read(1));
}

TEST_F(InstructionTest, INCZeroFlagAffected) {
  busController.write(1, 0xFF);
  instr.INC(1);
  GTEST_ASSERT_EQ(0x0, busController.read(1));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Zero));
}

TEST_F(InstructionTest, INCNegativeFlagAffected) {
  busController.write(1, 0xFD);
  instr.INC(1);
  GTEST_ASSERT_EQ(0xFE, busController.read(1));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Negative));
}

TEST_F(InstructionTest, INXWithNotFlagChanged) {
  registerController.setRegisterValue(X, 0x98);
  instr.INX();
  GTEST_ASSERT_EQ(0x99, registerController.getRegisterValue(X));
}

TEST_F(InstructionTest, INXZeroFlagAffected) {
  registerController.setRegisterValue(X, 0xFF);
  instr.INX();
  GTEST_ASSERT_EQ(0x0, registerController.getRegisterValue(X));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Zero));
}

TEST_F(InstructionTest, INXNegativeFlagAffected) {
  registerController.setRegisterValue(X, 0xFE);
  instr.INX();
  GTEST_ASSERT_EQ(0xFF, registerController.getRegisterValue(X));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Negative));
}

TEST_F(InstructionTest, INYWithNotFlagChanged) {
  registerController.setRegisterValue(Y, 0x98);
  instr.INY();
  GTEST_ASSERT_EQ(0x99, registerController.getRegisterValue(Y));
}

TEST_F(InstructionTest, INYZeroFlagAffected) {
  registerController.setRegisterValue(Y, 0xFF);
  instr.INY();
  GTEST_ASSERT_EQ(0x0, registerController.getRegisterValue(Y));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Zero));
}

TEST_F(InstructionTest, INYNegativeFlagAffected) {
  registerController.setRegisterValue(Y, 0xFE);
  instr.INY();
  GTEST_ASSERT_EQ(0xFF, registerController.getRegisterValue(Y));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Negative));
}

TEST_F(InstructionTest, ANDWithNotFlagChanged) {
  registerController.setRegisterValue(A, 0x3);
  busController.write(1, 0x5);
  instr.AND(1);
  GTEST_ASSERT_EQ(0x1, registerController.getRegisterValue(A));
}

TEST_F(InstructionTest, ANDZeroFlagAffected) {
  registerController.setRegisterValue(A, 0x0);
  busController.write(1, 0x5);
  instr.AND(1);
  GTEST_ASSERT_EQ(0x0, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Zero));
}

TEST_F(InstructionTest, ANDNegativeFlagAffected) {
  registerController.setRegisterValue(A, 0xFE);
  busController.write(1, 0xFF);
  instr.AND(1);
  GTEST_ASSERT_EQ(0xFE, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Negative));
}

TEST_F(InstructionTest, EORWithNotFlagChanged) {
  registerController.setRegisterValue(A, 0x3);
  busController.write(1, 0x5);
  instr.EOR(1);
  GTEST_ASSERT_EQ(0x6, registerController.getRegisterValue(A));
}

TEST_F(InstructionTest, EORZeroFlagAffected) {
  registerController.setRegisterValue(A, 0x0);
  busController.write(1, 0x0);
  instr.EOR(1);
  GTEST_ASSERT_EQ(0x0, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Zero));
}

TEST_F(InstructionTest, EORNegativeFlagAffected) {
  registerController.setRegisterValue(A, 0xF2);
  busController.write(1, 0x2);
  instr.EOR(1);
  GTEST_ASSERT_EQ(0xF0, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Negative));
}