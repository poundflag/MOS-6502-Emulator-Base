#include "addressmodeconversion.h"

AddressModeConversion::AddressModeConversion(
    RegisterController &registerController, BusController &busController)
    : registerController{registerController}, busController{busController} {}

uint8_t AddressModeConversion::absolute(uint16_t address) {
  return busController.read(address);
}

uint8_t AddressModeConversion::absoluteXIndexed(uint16_t address) {
  return absolute(address + registerController.getRegisterValue(X));
}

uint8_t AddressModeConversion::absoluteYIndexed(uint16_t address) {
  return absolute(address + registerController.getRegisterValue(Y));
}

uint8_t AddressModeConversion::zeroPage(uint8_t address) {
  return absolute(address);
}

uint8_t AddressModeConversion::zeroPageXIndexed(uint8_t address) {
  return absolute((address + registerController.getRegisterValue(X)) & 0xFF);
}

uint8_t AddressModeConversion::zeroPageYIndexed(uint8_t address) {
  return absolute((address + registerController.getRegisterValue(Y)) & 0xFF);
}

uint16_t AddressModeConversion::absoluteIndirect(uint16_t address) {
  uint8_t addressLSB = busController.read(address);
  uint8_t addressMSB = busController.read(address + 1);
  return (addressMSB << 8) | addressLSB;
}

uint8_t AddressModeConversion::indexedIndirect(uint8_t address) {
  uint16_t temp = (address + registerController.getRegisterValue(X)) & 0xFF;

  uint8_t addressLSB = busController.read(temp);
  uint8_t addressMSB = busController.read((temp + 1) & 0xFF);
  return busController.read((addressMSB << 8) | addressLSB);
}

uint8_t AddressModeConversion::indirectIndexed(uint8_t address) {

  uint8_t temp =
      (absolute(address) + registerController.getRegisterValue(Y)) & 0xFF;
  uint8_t temp1 = (absolute((address + 1) & 0xFF) +
                   registerController.getStatusRegister()->getStatus(Carry)) &
                  0xFF;

  return busController.read((temp1 << 8) | temp);
}
