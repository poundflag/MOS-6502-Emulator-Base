#include "busdevice.h"

BusDevice::BusDevice() { index = 0; }

void BusDevice::addAddress(AddressRange address) {
  if (index < ADDRESS_ARRAY_SIZE) {
    addresses[index] = address;
    index++;
  }
}

AddressRange *BusDevice::getAddresses() {
  if (index > 0) {
    return addresses;
  }
  return NULL;
}

BusDevice::~BusDevice() {
  delete[] addresses;
}
