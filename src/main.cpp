#include <iostream>
#include "register/registercontroller.h"

int main() {
    std::cout << "Hello";
    RegisterController l;
    l.setRegisterValue(A, 'X');
    std::cout << l.getRegisterValue(A);
}