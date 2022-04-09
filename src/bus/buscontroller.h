#include "model/busdevice.h"
#include "model/ram.h"
#include <stdint.h>
#include <stdio.h>

#ifndef __BUSCONTROLLER_H__
#define __BUSCONTROLLER_H__

const int BUS_DEVICE_ARRAY_SIZE = 100;

class BusController {
private:
  BusDevice **busDeviceArray;
  int arrayIndex;

  BusDevice *getDevice(uint16_t address);
  AddressRange getAddressRange(uint16_t address, BusDevice *currentDevice);

public:
  BusController();

  // Add a BusDevice to be interfaced with
  void addDevice(BusDevice *busDevice);
  void addRamChip(uint16_t startAddress, uint16_t endAddress);

  // Read a value from the bus
  uint8_t read(uint16_t address);

  // Write a value to the address
  void write(uint16_t address, uint8_t value);

  ~BusController();
};

#endif // __BUSCONTROLLER_H__