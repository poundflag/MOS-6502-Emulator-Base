#include "../../src/instruction/addressmodeconversion.h"
#include "../../src/bus/buscontroller.h"
#include "../../src/bus/model/busdevice.h"
#include "../../src/bus/model/ram.h"
#include "../../src/register/model/stack.h"
#include "../../src/register/registercontroller.h"
#include <gtest/gtest.h>

class AddressModeConversionTest : public ::testing::Test {
protected:
  BusController busController = BusController();
  Ram *ram = new Ram(0x10);
  Ram *stackRam = new Ram(0x100);
  RegisterController registerController = RegisterController(busController);
  AddressModeConversion adrConv =
      AddressModeConversion(registerController, busController);
  void SetUp() {
    ram->addAddress({0x1000, 0x1010});
    busController.addDevice(ram);
    stackRam->addAddress({0x0000, 0x00FF});
    busController.addDevice(stackRam);
  }
};

TEST_F(AddressModeConversionTest, absolute) {
  busController.write(0x1000, 0x5C);
  GTEST_ASSERT_EQ(0x5C, adrConv.absolute(0x1000));
}

TEST_F(AddressModeConversionTest, absoluteXIndexed) {
  registerController.setRegisterValue(X, 0xA3);
  busController.write(0x1005, 0x80);
  GTEST_ASSERT_EQ(0x80, adrConv.absoluteXIndexed(0x0F62));
}

TEST_F(AddressModeConversionTest, absoluteYIndexed) {
  registerController.setRegisterValue(Y, 0xA3);
  busController.write(0x1005, 0x81);
  GTEST_ASSERT_EQ(0x81, adrConv.absoluteYIndexed(0x0F62));
}

TEST_F(AddressModeConversionTest, zeroPage) {
  busController.write(0x0056, 0x1D);
  GTEST_ASSERT_EQ(0x1D, adrConv.zeroPage(0x0056));
}

TEST_F(AddressModeConversionTest, zeroPageXIndexed) {
  registerController.setRegisterValue(X, 0xE9);
  busController.write(0x003A, 0x04);
  GTEST_ASSERT_EQ(0x04, adrConv.zeroPageXIndexed(0x0051));
}

TEST_F(AddressModeConversionTest, zeroPageYIndexed) {
  registerController.setRegisterValue(Y, 0xE9);
  busController.write(0x003B, 0x04);
  GTEST_ASSERT_EQ(0x04, adrConv.zeroPageYIndexed(0x0052));
}

TEST_F(AddressModeConversionTest, absoluteIndirect) {
  busController.write(0x1009, 0x31);
  busController.write(0x100A, 0x88);
  GTEST_ASSERT_EQ(0x8831, adrConv.absoluteIndirect(0x1009));
}

TEST_F(AddressModeConversionTest, indexedIndirect) {
  registerController.setRegisterValue(X, 0xE9);
  busController.write(0x1007, 0x81);
  busController.write(0x3A, 0x07);
  busController.write(0x3B, 0x10);
  GTEST_ASSERT_EQ(0x81, adrConv.indexedIndirect(0x51));
}

TEST_F(AddressModeConversionTest, indirectIndexed) {
  registerController.setRegisterValue(Y, 0xE9);
  registerController.getStatusRegister()->setStatus(Carry, 1);
  busController.write(0x1007, 0xBB);
  busController.write(0xA4, 0x1E);
  busController.write(0xA5, 0x0F);
  GTEST_ASSERT_EQ(0xBB, adrConv.indirectIndexed(0xA4));
}