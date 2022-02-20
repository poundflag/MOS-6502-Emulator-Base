#include "registercontroller.h"

RegisterController::RegisterController() {
  registerArray = new Register *[STATE_COUNT];
  registerArray[STATUS] = statusRegister;
}

uint8_t RegisterController::getRegisterValue(Registers registerIndex) {
  return 0;
}

StatusRegister *RegisterController::getStatusRegister() { return statusRegister; }

void RegisterController::setRegisterValue(Registers registerIndex,
                                          uint8_t value) {
  // registerArray[registerIndex].setValue(value);
}

RegisterController::~RegisterController() {
  delete[] registerArray;
  delete statusRegister;
}
