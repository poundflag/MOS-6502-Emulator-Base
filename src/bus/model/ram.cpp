#include "ram.h"

Ram::Ram(uint16_t ramSize) {
  ramArray = new uint8_t[ramSize];
  this->ramSize = ramSize;
}

uint8_t Ram::read(uint16_t address) {
  // std::cout << "Read" << std::hex << address;
  if (ramSize >= address) {
    return ramArray[address];
  }
  return 0;
}

void Ram::write(uint16_t address, uint8_t value) {
  // std::cout << std::hex << address;
  if (ramSize >= address) {
    ramArray[address] = value;
  }
}

Ram::~Ram() { delete ramArray; }
