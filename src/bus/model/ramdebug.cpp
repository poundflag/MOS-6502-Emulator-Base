#include "ramdebug.h"

RamDebug::RamDebug(std::string fullFilePath) { loadRomFile(fullFilePath); }

void RamDebug::loadRomFile(std::string fullFilePath) {

  std::ifstream myfile(fullFilePath, std::ios::binary | std::ios::ate);
  // fstream file("sample.bin",  ios::out | ios::binary);
  // Initialize new array with the size of file
  ram = new int[determineSize(myfile)];
  int i = 0;
  if (myfile.is_open()) {

    // While there are still bytes left to read
    while (myfile.good()) {
      // Add the byte to the ram array
      ram[i] = myfile.get();
      if (ram[i] == -1) {
        ram[i] = 0;
        break;
      }
      // std::cout << "PC " << (int)i << " " << (int)ram[i] << std::endl;

      i++;
    }
    myfile.close();
  }

  else {
    std::cout << "Unable to open file";
  }
}

int RamDebug::determineSize(std::ifstream &file) {
  // If the file is open
  if (file.is_open()) {
    // Get the size of file
    int fileSize = file.tellg();
    // Reset its cursor position
    file.seekg(std::ios_base::beg);
    return fileSize;
  }
  return -1;
}

void RamDebug::write(uint16_t address, uint8_t value) { ram[address] = value; }

uint8_t RamDebug::read(uint16_t address) { return ram[address]; }

RamDebug::~RamDebug() { delete[] ram; }
