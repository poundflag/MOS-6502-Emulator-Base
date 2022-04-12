#include "statusregister.h"
#include <iostream>

StatusRegister::StatusRegister() {}

void StatusRegister::setValue(uint8_t value1, uint8_t value2) {
  uint16_t result = value1 + value2;
  setZero(result);
  setNegative(result);
  setOverflow(value1, value2);
  setCarry(result);
}

uint8_t StatusRegister::getValue() { return this->value | 0b00110000; }

void StatusRegister::overrideValue(uint8_t value) { this->value = value; }

void StatusRegister::setCarry(uint16_t value) {
  setStatus(Carry, ((value >> 8) & 1) == 1);
}

void StatusRegister::setZero(uint8_t value) {
  // std::setvbuf(stdout, NULL, _IONBF, 0);
  // std::cout << value;
  setStatus(Zero, value == 0);
}

void StatusRegister::setOverflow(uint8_t value1, uint8_t value2) {
  uint8_t m = value2;
  uint8_t tmp = m + value1 + (getStatus(Carry) ? 1 : 0);

  bool re = (!((value1 ^ m) & 0x80) && ((value1 ^ tmp) & 0x80));

  setStatus(Overflow, re);
}

void StatusRegister::setNegative(uint8_t value) {
  setStatus(Negative, ((value >> 7) & 1) == 1);
}

void StatusRegister::setStatus(Flag flag, bool state) {
  if (state) {
    value |= (1 << flag);
  } else {
    value &= ~(1 << flag);
  }
}

bool StatusRegister::getStatus(Flag flag) { return ((value >> flag) & 1) == 1; }
