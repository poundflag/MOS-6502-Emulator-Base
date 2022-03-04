#include <gtest/gtest.h>

class RegisterControllerTest : public ::testing::Test {
  // protected:
};
// TODO Add test?? At least for the stack then
TEST(RegisterControllerTest, readFromFirstPage) {
  GTEST_ASSERT_EQ(1, 0x1);
}