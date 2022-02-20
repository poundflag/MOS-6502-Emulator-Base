add_subdirectory(googletest) # add googletest subdirectory

include_directories(googletest/include) # this is so we can #include <gtest/gtest.h>

add_executable(test test.cpp)

target_link_libraries(test 
    PRIVATE gtest # link google test to this executable
    PRIVATE buscontroller
    PRIVATE registercontroller
)
