add_library(register model/register.cpp)

add_library(registercontroller registercontroller.cpp)

target_link_libraries(registercontroller PRIVATE register)
