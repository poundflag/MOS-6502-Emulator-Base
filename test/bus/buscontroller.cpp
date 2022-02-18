#include "../../src/bus/buscontroller.h"
#include "../../src/bus/model/busdevice.h"
#include "../../src/bus/model/ram.h"
#include <gtest/gtest.h>

class BusControllerTest : public ::testing::Test {
protected:
  BusController busController = BusController();
  void SetUp() {
    Ram *ram = new Ram(0x11);
    ram->addAddress({0xEF, 0xFF});
    ram->write(0x10, 0x12);
    ram->write(0x4, 0x88);
    busController.addDevice(ram);
  }
};

TEST_F(BusControllerTest, readFromFirstPage) {
  GTEST_ASSERT_EQ(busController.read(0), 0x0);
}

TEST_F(BusControllerTest, readFromPopulatedPage) {
  GTEST_ASSERT_EQ(busController.read(0xF3), 0x88);
}

TEST_F(BusControllerTest, readFromLastPopulatedPage) {
  GTEST_ASSERT_EQ(busController.read(0xFF), 0x12);
}

TEST_F(BusControllerTest, readFromLastUnpopulatedPage) {
  GTEST_ASSERT_EQ(busController.read(0xFFFF), 0x0);
}