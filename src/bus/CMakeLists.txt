add_library(busdevice model/busdevice.cpp)

add_library(ram model/ram.cpp)

add_library(ramDebug model/ramdebug.cpp)

add_library(buscontroller buscontroller.cpp)

target_link_libraries(buscontroller
    PRIVATE busdevice
    PRIVATE ram
    PRIVATE ramDebug
)