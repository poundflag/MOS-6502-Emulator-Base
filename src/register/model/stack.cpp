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
