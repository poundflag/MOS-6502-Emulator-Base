#include "../../src/instruction/instruction.h"
#include "../../src/alu.h"
#include "../../src/bus/buscontroller.h"
#include "../../src/bus/model/busdevice.h"
#include "../../src/bus/model/ram.h"
#include "../../src/register/model/stack.h"
#include "../../src/register/registercontroller.h"
#include <gtest/gtest.h>

class InstructionTest : public ::testing::Test {
protected:
  BusController busController = BusController();
  Ram *ram = new Ram(0x10);
  Ram *stackRam = new Ram(0x100);
  RegisterController registerController = RegisterController(busController);
  ALU alu = ALU(registerController);
  Instruction instr = Instruction(registerController, busController, alu);
  void SetUp() {
    ram->addAddress({0x0, 0x10});
    busController.addDevice(ram);
    stackRam->addAddress({0x0100, 0x01FF});
    busController.addDevice(stackRam);
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
  instr.EOR(5);
  GTEST_ASSERT_EQ(0x6, registerController.getRegisterValue(A));
}

TEST_F(InstructionTest, EORZeroFlagAffected) {
  registerController.setRegisterValue(A, 0x0);
  instr.EOR(0);
  GTEST_ASSERT_EQ(0x0, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Zero));
}

TEST_F(InstructionTest, EORNegativeFlagAffected) {
  registerController.setRegisterValue(A, 0xF2);
  instr.EOR(2);
  GTEST_ASSERT_EQ(0xF0, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Negative));
}

TEST_F(InstructionTest, ORAWithNotFlagChanged) {
  registerController.setRegisterValue(A, 0x3);
  busController.write(1, 0x5);
  instr.ORA(1);
  GTEST_ASSERT_EQ(0x7, registerController.getRegisterValue(A));
}

TEST_F(InstructionTest, ORAZeroFlagAffected) {
  registerController.setRegisterValue(A, 0x0);
  busController.write(1, 0x0);
  instr.ORA(1);
  GTEST_ASSERT_EQ(0x0, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Zero));
}

TEST_F(InstructionTest, ORANegativeFlagAffected) {
  registerController.setRegisterValue(A, 0xF2);
  busController.write(1, 0x2);
  instr.ORA(1);
  GTEST_ASSERT_EQ(0xF2, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Negative));
}

TEST_F(InstructionTest, TAXWithNotFlagChanged) {
  registerController.setRegisterValue(A, 0x3);
  registerController.setRegisterValue(X, 0x5);
  instr.TAX();
  GTEST_ASSERT_EQ(0x3, registerController.getRegisterValue(X));
}

TEST_F(InstructionTest, TAXZeroFlagAffected) {
  registerController.setRegisterValue(A, 0x0);
  registerController.setRegisterValue(X, 0x5);
  instr.TAX();
  GTEST_ASSERT_EQ(0x0, registerController.getRegisterValue(X));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Zero));
}

TEST_F(InstructionTest, TAXNegativeFlagAffected) {
  registerController.setRegisterValue(A, 0xF3);
  registerController.setRegisterValue(X, 0x5);
  instr.TAX();
  GTEST_ASSERT_EQ(0xF3, registerController.getRegisterValue(X));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Negative));
}

TEST_F(InstructionTest, TAYWithNotFlagChanged) {
  registerController.setRegisterValue(A, 0x3);
  registerController.setRegisterValue(Y, 0x5);
  instr.TAY();
  GTEST_ASSERT_EQ(0x3, registerController.getRegisterValue(Y));
}

TEST_F(InstructionTest, TAYZeroFlagAffected) {
  registerController.setRegisterValue(A, 0x0);
  registerController.setRegisterValue(Y, 0x5);
  instr.TAY();
  GTEST_ASSERT_EQ(0x0, registerController.getRegisterValue(Y));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Zero));
}

TEST_F(InstructionTest, TAYNegativeFlagAffected) {
  registerController.setRegisterValue(A, 0xF3);
  registerController.setRegisterValue(Y, 0x5);
  instr.TAY();
  GTEST_ASSERT_EQ(0xF3, registerController.getRegisterValue(Y));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Negative));
}

TEST_F(InstructionTest, TXAWithNotFlagChanged) {
  registerController.setRegisterValue(X, 0x3);
  registerController.setRegisterValue(A, 0x5);
  instr.TXA();
  GTEST_ASSERT_EQ(0x3, registerController.getRegisterValue(A));
}

TEST_F(InstructionTest, TXAZeroFlagAffected) {
  registerController.setRegisterValue(X, 0x0);
  registerController.setRegisterValue(A, 0x5);
  instr.TXA();
  GTEST_ASSERT_EQ(0x0, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Zero));
}

TEST_F(InstructionTest, TXANegativeFlagAffected) {
  registerController.setRegisterValue(X, 0xF3);
  registerController.setRegisterValue(A, 0x5);
  instr.TXA();
  GTEST_ASSERT_EQ(0xF3, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Negative));
}

TEST_F(InstructionTest, TYAWithNotFlagChanged) {
  registerController.setRegisterValue(Y, 0x3);
  registerController.setRegisterValue(A, 0x5);
  instr.TYA();
  GTEST_ASSERT_EQ(0x3, registerController.getRegisterValue(A));
}

TEST_F(InstructionTest, TYAZeroFlagAffected) {
  registerController.setRegisterValue(Y, 0x0);
  registerController.setRegisterValue(A, 0x5);
  instr.TYA();
  GTEST_ASSERT_EQ(0x0, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Zero));
}

TEST_F(InstructionTest, TYANegativeFlagAffected) {
  registerController.setRegisterValue(Y, 0xF3);
  registerController.setRegisterValue(A, 0x5);
  instr.TYA();
  GTEST_ASSERT_EQ(0xF3, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Negative));
}

TEST_F(InstructionTest, TSXWithNotFlagChanged) {
  registerController.getStack()->push(0x10);
  registerController.setRegisterValue(X, 0x5);
  instr.TSX();
  GTEST_ASSERT_EQ(0xFE, registerController.getRegisterValue(X));
}

TEST_F(InstructionTest, TXSWithNotFlagChanged) {
  registerController.getStack()->push(0x10);
  registerController.setRegisterValue(X, 0x5);
  instr.TXS();
  GTEST_ASSERT_EQ(0x0, registerController.getStack()->pull());
}

TEST_F(InstructionTest, TXSZeroFlagAffected) {
  registerController.getStack()->push(0x5);
  registerController.getStack()->push(0x5);
  registerController.setRegisterValue(X, 0x0);
  instr.TXS();
  GTEST_ASSERT_EQ(0x0, registerController.getStack()->pull());
}

TEST_F(InstructionTest, TXSNegativeFlagAffected) {
  registerController.getStack()->push(0x5);
  registerController.setRegisterValue(X, 0xF3);
  instr.TXS();
  GTEST_ASSERT_EQ(0xF3, registerController.getStack()->getValue());
}

TEST_F(InstructionTest, PHA) {
  registerController.setRegisterValue(A, 0x44);
  instr.PHA();
  GTEST_ASSERT_EQ(0x44, registerController.getStack()->pull());
}

TEST_F(InstructionTest, PHP) {
  registerController.getStatusRegister()->Register::setValue(0x20);
  instr.PHP();
  GTEST_ASSERT_EQ(0x30, registerController.getStack()->pull());
}

TEST_F(InstructionTest, PLA) {
  registerController.getStack()->push(0x34);
  instr.PLA();
  GTEST_ASSERT_EQ(0x34, registerController.getRegisterValue(A));
}

TEST_F(InstructionTest, PLP) {
  registerController.getStack()->push(0x34);
  instr.PLP();
  GTEST_ASSERT_EQ(0x34, registerController.getStatusRegister()->getValue());
}

TEST_F(InstructionTest, ADCWithSimpleNumbers) {
  registerController.setRegisterValue(A, 0x3);
  instr.ADC(0x3);
  GTEST_ASSERT_EQ(0x6, registerController.getRegisterValue(A));
}

TEST_F(InstructionTest, ADCWithSimpleCarryFlagAndOverflow) {
  registerController.setRegisterValue(A, 0xFF);
  instr.ADC(0xFF);
  GTEST_ASSERT_EQ(0xFE, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Negative));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Carry));
}

TEST_F(InstructionTest, ADCWithSimpleCarryFlagAndOverflow2) {
  registerController.setRegisterValue(A, 0xFA);
  instr.ADC(0x0A);
  GTEST_ASSERT_EQ(0x04, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Carry));
}

TEST_F(InstructionTest, ADCWithCarryFlagTrue) {
  registerController.getStatusRegister()->setStatus(Carry, true);
  registerController.setRegisterValue(A, 0x2);
  instr.ADC(0x02);
  GTEST_ASSERT_EQ(0x05, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(false,
                  registerController.getStatusRegister()->getStatus(Carry));
}

TEST_F(InstructionTest, ADCWithCarryFlagTrueAndOverflow) {
  registerController.getStatusRegister()->setStatus(Carry, true);
  registerController.setRegisterValue(A, 0xFE);
  instr.ADC(0x0FE);
  GTEST_ASSERT_EQ(0xFD, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Carry));
}

TEST_F(InstructionTest, ADCWithCarryFlagTrueAndOverflow2) {
  registerController.getStatusRegister()->setStatus(Carry, true);
  registerController.setRegisterValue(A, 0xFF);
  instr.ADC(0x0FF);
  GTEST_ASSERT_EQ(0xFF, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Carry));
}

TEST_F(InstructionTest,
       ASLMemorySimpleShiftWithTheCarryBeingZeroAndNothingElseSet) {
  busController.write(0x2, 2);
  instr.ASL_Memory(0x2);
  GTEST_ASSERT_EQ(0x4, busController.read(0x2));
  GTEST_ASSERT_EQ(false,
                  registerController.getStatusRegister()->getStatus(Carry));
}

TEST_F(InstructionTest, ASLMemorySimpleShiftWithTheCarryBeingSetAndZero) {
  busController.write(0x2, 0x80);
  instr.ASL_Memory(0x2);
  GTEST_ASSERT_EQ(0x00, busController.read(0x2));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Carry));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Zero));
}

TEST_F(InstructionTest, ASLMemorySimpleShiftWithNegativeBeingSet) {
  busController.write(0x2, 0x70);
  instr.ASL_Memory(0x2);
  GTEST_ASSERT_EQ(0xE0, busController.read(0x2));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Negative));
}

TEST_F(InstructionTest,
       LSRMemorySimpleShiftWithTheCarryBeingZeroAndNothingElseSet) {
  busController.write(0x2, 2);
  instr.LSR_Memory(0x2);
  GTEST_ASSERT_EQ(0x1, busController.read(0x2));
  GTEST_ASSERT_EQ(false,
                  registerController.getStatusRegister()->getStatus(Carry));
}

TEST_F(InstructionTest, LSRMemorySimpleShiftWithTheCarryBeingSetAndZero) {
  busController.write(0x2, 0x1);
  instr.LSR_Memory(0x2);
  GTEST_ASSERT_EQ(0x00, busController.read(0x2));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Carry));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Zero));
}

TEST_F(InstructionTest, LSRMemorySimpleShiftWithNegativeBeingZero) {
  registerController.getStatusRegister()->setStatus(Carry, true);
  busController.write(0x2, 0xF9);
  instr.LSR_Memory(0x2);
  GTEST_ASSERT_EQ(0x7C, busController.read(0x2));
  GTEST_ASSERT_EQ(false,
                  registerController.getStatusRegister()->getStatus(Negative));
}

TEST_F(InstructionTest, ROLMemoryWithTheCarryOn) {
  registerController.getStatusRegister()->setStatus(Carry, true);
  busController.write(0x2, 0x4);
  instr.ROL_Memory(0x2);
  GTEST_ASSERT_EQ(0x9, busController.read(0x2));
  GTEST_ASSERT_EQ(false,
                  registerController.getStatusRegister()->getStatus(Carry));
}

TEST_F(InstructionTest, ROLMemoryWithTheCarryOff) {
  registerController.getStatusRegister()->setStatus(Carry, false);
  busController.write(0x2, 0x4);
  instr.ROL_Memory(0x2);
  GTEST_ASSERT_EQ(0x8, busController.read(0x2));
  GTEST_ASSERT_EQ(false,
                  registerController.getStatusRegister()->getStatus(Carry));
}

TEST_F(InstructionTest, ROLMemoryWithTheCarryOnAndAnOverflow) {
  registerController.getStatusRegister()->setStatus(Carry, true);
  busController.write(0x2, 0xFF);
  instr.ROL_Memory(0x2);
  GTEST_ASSERT_EQ(0xFF, busController.read(0x2));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Carry));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Negative));
}

TEST_F(InstructionTest, RORMemoryWithTheCarryOn) {
  registerController.getStatusRegister()->setStatus(Carry, true);
  busController.write(0x2, 0x2);
  instr.ROR_Memory(0x2);
  GTEST_ASSERT_EQ(0x81, busController.read(0x2));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Negative));
  GTEST_ASSERT_EQ(false,
                  registerController.getStatusRegister()->getStatus(Carry));
}

TEST_F(InstructionTest, RORMemoryWithTheCarryOff) {
  registerController.getStatusRegister()->setStatus(Carry, false);
  busController.write(0x2, 0x2);
  instr.ROR_Memory(0x2);
  GTEST_ASSERT_EQ(0x1, busController.read(0x2));
  GTEST_ASSERT_EQ(false,
                  registerController.getStatusRegister()->getStatus(Carry));
}

TEST_F(InstructionTest, RORMemoryWithTheCarryOnAndAnOverflow) {
  registerController.getStatusRegister()->setStatus(Carry, true);
  busController.write(0x2, 0xFF);
  instr.ROR_Memory(0x2);
  GTEST_ASSERT_EQ(0xFF, busController.read(0x2));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Carry));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Negative));
}

TEST_F(InstructionTest, SBCWithSimpleNumbersAndCarryOff) {
  registerController.setRegisterValue(A, 0x6);
  instr.SBC(0x4);
  GTEST_ASSERT_EQ(0x1, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Carry));
}

TEST_F(InstructionTest, SBCWithSimpleNumbersAndCarryOn) {
  registerController.getStatusRegister()->setStatus(Carry, true);
  registerController.setRegisterValue(A, 0x6);
  instr.SBC(0x4);
  GTEST_ASSERT_EQ(0x2, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Carry));
}

TEST_F(InstructionTest, SBCWithSimpleCarryFlagAndOverflow) {
  registerController.getStatusRegister()->setStatus(Carry, true);
  registerController.setRegisterValue(A, 0xD0);
  instr.SBC(0x70);
  GTEST_ASSERT_EQ(0x60, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Overflow));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Carry));
}

TEST_F(InstructionTest, SBCWithSimpleCarryFlagAndOverflow2) {
  registerController.getStatusRegister()->setStatus(Carry, true);
  registerController.setRegisterValue(A, 0x50);
  instr.SBC(0xB0);
  GTEST_ASSERT_EQ(0xA0, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(false,
                  registerController.getStatusRegister()->getStatus(Carry));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Overflow));
}

TEST_F(InstructionTest, JMP) {
  registerController.setProgramCounter(0x1234);
  instr.JMP(0x4321);
  GTEST_ASSERT_EQ(0x4320, registerController.getProgramCounter());
}

// TODO Add branching tests!!!
// TODO CMP
// TODO JSR

TEST_F(InstructionTest, BITWithZeroSet) {
  busController.write(2, 5);
  registerController.setRegisterValue(A, 0xA);
  instr.BIT(2);
  GTEST_ASSERT_EQ(0xA, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Zero));
  GTEST_ASSERT_EQ(false,
                  registerController.getStatusRegister()->getStatus(Negative));
}

TEST_F(InstructionTest, BITWithNegativeAndOverflowSet) {
  busController.write(2, 0xFF);
  registerController.setRegisterValue(A, 0xF3);
  instr.BIT(2);
  GTEST_ASSERT_EQ(0xF3, registerController.getRegisterValue(A));
  GTEST_ASSERT_EQ(false,
                  registerController.getStatusRegister()->getStatus(Zero));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Negative));
  GTEST_ASSERT_EQ(true,
                  registerController.getStatusRegister()->getStatus(Overflow));
}