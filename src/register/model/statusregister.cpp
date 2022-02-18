#include "statusregister.h"

StatusRegister::StatusRegister() { this->value = 0b00000100; }

void StatusRegister::processStatus(uint8_t value) {}

bool StatusRegister::getStatus(Status status) {
  return (this->value << status) == 1;
}
