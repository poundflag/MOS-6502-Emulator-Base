#include <gtest/gtest.h>
#include "bus/buscontroller.cpp"
#include "register/model/statusregister.cpp"
#include "register/registercontroller.cpp"
/*
TEST(myfunctions, add)
{
    GTEST_ASSERT_EQ(1, 1);
}
*/
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}