#include "registercontroller.h"

RegisterController::RegisterController() {
  statusRegister = new StatusRegister();
  // TODO Change size
  registerArray = new Register[STATE_COUNT];
}

uint8_t RegisterController::getRegisterValue(Registers registerIndex) {
  return registerArray[registerIndex].getValue();
}

StatusRegister *RegisterController::getStatusRegister() {
  return statusRegister;
}

void RegisterController::setRegisterValue(Registers registerIndex,
                                          uint8_t value) {
  registerArray[registerIndex].setValue(value);
}

RegisterController::~RegisterController() {
  delete statusRegister;
  delete[] registerArray;
}
