#include "registercontroller.h"

uint8_t RegisterController::getRegisterValue(Registers registerIndex) {
  return registerArray[registerIndex].getValue();
}

void RegisterController::setRegisterValue(Registers registerIndex,
                                          uint8_t value) {
  registerArray[registerIndex].setValue(value);
}
