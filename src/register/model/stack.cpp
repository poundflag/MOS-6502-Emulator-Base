#include "stack.h"

Stack::Stack(BusController &busController) : busController{busController} {}

void Stack::push(uint8_t data) {
  busController.write(STACK_POINTER_PREFIX + value, data);
  value++;
}

uint8_t Stack::pull() {
  value--;
  return busController.read(STACK_POINTER_PREFIX + value);
}

void Stack::pushWord(uint16_t data) {
  push(data >> 8);
  push(data & 0xFF);
}

uint16_t Stack::pullWord() { return pull() | (pull() << 8); }
