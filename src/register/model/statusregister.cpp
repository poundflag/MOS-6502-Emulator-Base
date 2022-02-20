#include "statusregister.h"

StatusRegister::StatusRegister() { this->value = 0b00000100; }

void StatusRegister::setValue(uint8_t value1, uint8_t value2) {
  uint16_t result = value1 + value2;
  setZero(result);
  setNegative(result);
  setCarry(result);
  setOverflow(value1, value2);
}

void StatusRegister::overrideValue(uint8_t value) { this->value = value; }

void StatusRegister::setCarry(uint16_t value) {
  setStatus(Carry, ((value >> 8) & 1) == 1);
}

void StatusRegister::setZero(uint8_t value) { setStatus(Zero, value == 0); }

void StatusRegister::setOverflow(uint8_t value1, uint8_t value2) {
  // Dont't know why it wants the carry flipped :/
  uint16_t result = (value1 + value2 + (getStatus(Carry) ? 0 : 1));
  // Check if the result of two complements is overflowed
  // -> If an xor of two values results in a 0 (in the last bit) it is overflowed
  // However also the opposite needs to be checked if it hasn't overflowed
  bool re = !((value1 ^ value2) & 0x80) && ((value1 ^ result) & 0x80);
  // std::cout << std::hex << re << std::endl;
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
