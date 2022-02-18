add_library(buscontrollertest buscontroller.cpp)

add_library(buscontroller ../../src/bus/buscontroller.cpp)

add_library(busdevice ../../src/bus/model/busdevice.cpp)

add_library(ram ../../src/bus/model/ram.cpp)

target_link_libraries(buscontrollertest
    PRIVATE buscontroller
    PRIVATE busdevice
    PRIVATE ram
)