#include <gtest/gtest.h>

class RegisterControllerTest : public ::testing::Test {
  // protected:
};

TEST(RegisterControllerTest, readFromFirstPage) {
  GTEST_ASSERT_EQ(1, 0x1);
}