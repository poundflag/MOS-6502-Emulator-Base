#include <gtest/gtest.h>

class InstructionTest : public ::testing::Test {
protected:
  void SetUp() {}
};

TEST(InstructionTest, lll) {
  GTEST_ASSERT_EQ(0, 0x0);
}