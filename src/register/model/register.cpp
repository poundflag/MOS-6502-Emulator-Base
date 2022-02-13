#include "register.h"

Register::Register() { value = 0; }

void Register::setValue(uint8_t value) { this->value = value; }

uint8_t Register::getValue() { return this->value; }
