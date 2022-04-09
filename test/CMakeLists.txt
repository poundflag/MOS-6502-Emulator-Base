add_subdirectory(googletest) # add googletest subdirectory

include_directories(googletest/include) # this is so we can #include <gtest/gtest.h>

enable_testing()

add_library(instructionTest ../src/instruction/instruction.cpp)

add_executable(test test.cpp)

target_link_libraries(test 
    PUBLIC gtest # link google test to this executable
    PUBLIC buscontroller
    PUBLIC registercontroller
    PUBLIC instructionTest
    PUBLIC instruction
    PUBLIC alu
)

include(GoogleTest)