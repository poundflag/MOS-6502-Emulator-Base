#include <iostream>
#include "cpu.h"

int main() {
    std::cout << "Hello";
    CPU cpu = CPU();
    cpu.getBusController().addRamChip(0x0, 0xFF);
    cpu.getBusController().addRamChip(0xF000, 0xFFFF);

    cpu.getBusController().write(0xFFFC, 0x00);
    cpu.getBusController().write(0xFFFD, 0x00);

    /*cpu.getBusController().write(0, 0xA9); // LDA
    cpu.getBusController().write(1, 0x13);
    cpu.getBusController().write(2, 0x69); // ADC
    cpu.getBusController().write(3, 0x12);*/

    cpu.getBusController().write(0, 0xA2);
    cpu.getBusController().write(1, 0x11);
    cpu.getBusController().write(2, 0xE8);
    cpu.getBusController().write(3, 0x8A);
    cpu.getBusController().write(4, 0xC9);
    cpu.getBusController().write(5, 0x15);
    cpu.getBusController().write(6, 0xF0);
    cpu.getBusController().write(7, 0x03);
    cpu.getBusController().write(8, 0x20);
    cpu.getBusController().write(9, 0x02);
    cpu.getBusController().write(10, 0x00);
    cpu.getBusController().write(11, 0x00);


    cpu.step(25);
}