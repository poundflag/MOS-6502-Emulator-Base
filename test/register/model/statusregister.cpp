#include "../../../src/register/model/statusregister.h"
#include <gtest/gtest.h>

class StatusRegisterTest : public ::testing::Test {
protected:
  StatusRegister statusRegister = StatusRegister();
  void SetUp() {}
};

TEST_F(StatusRegisterTest, setZeroFlag) {
  statusRegister.setValue(0, 0);
  GTEST_ASSERT_EQ(statusRegister.getStatus(Zero), 1);
}

TEST_F(StatusRegisterTest, resetZeroFlag) {
  statusRegister.setValue(0, 1);
  GTEST_ASSERT_EQ(statusRegister.getStatus(Zero), 0);
}

TEST_F(StatusRegisterTest, setNegativeFlag) {
  statusRegister.setValue(128, 0);
  GTEST_ASSERT_EQ(statusRegister.getStatus(Negative), 1);
}

TEST_F(StatusRegisterTest, setNegativeFlag2) {
  statusRegister.setValue(0xFF, 0);
  GTEST_ASSERT_EQ(statusRegister.getStatus(Negative), 1);
}

TEST_F(StatusRegisterTest, resetNegativeFlag) {
  statusRegister.setValue(127, 0);
  GTEST_ASSERT_EQ(statusRegister.getStatus(Negative), 0);
}

TEST_F(StatusRegisterTest, setCarryFlag) {
  statusRegister.setValue(0xFF, 1);
  GTEST_ASSERT_EQ(statusRegister.getStatus(Carry), 1);
}

TEST_F(StatusRegisterTest, resetCarryFlag) {
  statusRegister.setValue(0xFF, 0);
  GTEST_ASSERT_EQ(statusRegister.getStatus(Carry), 0);
}

TEST_F(StatusRegisterTest, setOverflowFlag) {
  statusRegister.setValue(0xB0, 0xB0);
  GTEST_ASSERT_EQ(statusRegister.getStatus(Overflow), 1);
}

TEST_F(StatusRegisterTest, setOverflowFlag2) {
  statusRegister.setValue(0x7F, 0x01);
  GTEST_ASSERT_EQ(statusRegister.getStatus(Overflow), 1);
}

TEST_F(StatusRegisterTest, setOverflowFlag3) {
  statusRegister.setValue(0x80, 0xFF);
  GTEST_ASSERT_EQ(statusRegister.getStatus(Carry), 1);
  GTEST_ASSERT_EQ(statusRegister.getStatus(Overflow), 1);
}

TEST_F(StatusRegisterTest, resetOverflowFlag) {
  statusRegister.setValue(0xEC, 0xEC);
  GTEST_ASSERT_EQ(statusRegister.getStatus(Overflow), 0);
}

TEST_F(StatusRegisterTest, resetOverflowFlag2) {
  statusRegister.setValue(0x01, 0xFF);
  GTEST_ASSERT_EQ(statusRegister.getStatus(Overflow), 0);
}

TEST_F(StatusRegisterTest, resetOverflowFlag3) {
  statusRegister.setValue(0x1, 0x1);
  GTEST_ASSERT_EQ(statusRegister.getStatus(Overflow), 0);
}