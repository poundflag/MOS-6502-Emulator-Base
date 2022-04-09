#include "buscontroller.h"

BusController::BusController() {
  // Set the size of the busDeviceArray to the constant defined in the header
  busDeviceArray = new BusDevice *[BUS_DEVICE_ARRAY_SIZE];
  arrayIndex = 0;
}

BusDevice *BusController::getDevice(uint16_t address) {
  // Loop through all available devices
  for (int i = 0; i < arrayIndex; i++) {
    BusDevice *currentDevice = busDeviceArray[i];
    AddressRange addressRange = getAddressRange(address, currentDevice);
    // If an address has been found return the current device
    if (!addressRange.isAddressEmpty()) {
      return currentDevice;
    }
  }
  return NULL;
}

void BusController::addDevice(BusDevice *busDevice) {
  busDeviceArray[arrayIndex] = busDevice;
  arrayIndex++;
}

void BusController::addRamChip(uint16_t startAddress, uint16_t endAddress) {
  Ram *ram = new Ram(endAddress - startAddress);
  ram->addAddress({startAddress, endAddress});
  addDevice(ram);
}

AddressRange BusController::getAddressRange(uint16_t address,
                                            BusDevice *currentDevice) {
  if (currentDevice != NULL) {
    AddressRange *addressRange = currentDevice->getAddresses();
    if (addressRange != NULL) {

      for (int j = 0; j < ADDRESS_ARRAY_SIZE; j++) {
        AddressRange currentAddress = addressRange[j];

        if (!currentAddress.isAddressEmpty() &&
            address >= currentAddress.addressStart &&
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
  AddressRange addressRange = getAddressRange(address, currentDevice);
  if (currentDevice != NULL && !addressRange.isAddressEmpty()) {
    return currentDevice->read(address - addressRange.addressStart);
  }
  return 0;
}

void BusController::write(uint16_t address, uint8_t value) {
  BusDevice *currentDevice = getDevice(address);
  AddressRange addressRange = getAddressRange(address, currentDevice);
  if (currentDevice != NULL && !addressRange.isAddressEmpty()) {
    currentDevice->write(address - addressRange.addressStart, value);
  }
}

BusController::~BusController() { delete[] busDeviceArray; }
