#include "buscontroller.h"

BusController::BusController() {
  // Set the size of the busDeviceArray to the constant defined in the header
  busDeviceArray = new BusDevice *[BUS_DEVICE_ARRAY_SIZE];
  arrayIndex = 0;
}

BusDevice *BusController::getDevice(uint16_t address) {
  for (int i = 0; i < arrayIndex; i++) {
    BusDevice *currentDevice = busDeviceArray[i];
    // Refactor  TODO
    if (currentDevice->getAddresses() != NULL) {
      for (int j = 0; j < 5; j++) {
        AddressRange currentAddress = currentDevice->getAddresses()[j];
        if ((currentAddress.addressStart & currentAddress.addressEnd) != 0) {
          if (address >= currentAddress.addressStart &&
              address <= currentAddress.addressEnd) {
            return currentDevice;
          }
        }
      }
    }
  }
  return NULL;
}

void BusController::addDevice(BusDevice *busDevice) {
  busDeviceArray[arrayIndex] = busDevice;
  arrayIndex++;
}

// TODO Change name
AddressRange BusController::getAddressRange(uint16_t address) {
  AddressRange *addressRange = getDevice(address)->getAddresses();
  // TODO Add const for the 5 PLEASE!
  if (addressRange != NULL) {
    for (int j = 0; j < 5; j++) {
      AddressRange currentAddress = addressRange[j];
      if ((currentAddress.addressStart & currentAddress.addressEnd) != 0) {
        if (address >= currentAddress.addressStart &&
            address <= currentAddress.addressEnd) {
          return currentAddress;
        }
      }
    }
  }
  AddressRange notFoundRange = {0, 0};
  return notFoundRange;
}

uint8_t BusController::read(uint16_t address) {
  BusDevice *currentDevice = getDevice(address);
  if (currentDevice != NULL) {
    return currentDevice->read(address - getAddressRange(address).addressStart);
  }
  return 0;
}

void BusController::write(uint16_t address, uint8_t value) {
  BusDevice *currentDevice = getDevice(address);
  if (currentDevice != NULL) {
    currentDevice->write(address, value);
  }
}

BusController::~BusController() { delete[] busDeviceArray; }
