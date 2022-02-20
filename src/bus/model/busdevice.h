#include <iostream>
#include <stdint.h>
#include <stdio.h>

#ifndef __BUSDEVICE_H__
#define __BUSDEVICE_H__

struct AddressRange {
  uint16_t addressStart;
  uint16_t addressEnd;
  bool isAddressEmpty() { return (addressStart & addressEnd) == 0; }
};

static const int ADDRESS_ARRAY_SIZE = 5;

// Abstract class for the implementation of a bus device
class BusDevice {
private:
  AddressRange addresses[ADDRESS_ARRAY_SIZE];
  int index;

public:
  BusDevice();
  virtual uint8_t read(uint16_t address) = 0;
  virtual void write(uint16_t address, uint8_t value) = 0;
  void addAddress(AddressRange address);
  AddressRange *getAddresses();
  virtual ~BusDevice();
};

#endif // __BUSDEVICE_H__