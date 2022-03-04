add_library(register model/register.cpp)

add_library(statusregister model/statusregister.cpp)

add_library(stack model/stack.cpp)

add_library(registercontroller registercontroller.cpp)

target_link_libraries(registercontroller
    PRIVATE register
    PRIVATE statusregister
    PUBLIC stack
)
