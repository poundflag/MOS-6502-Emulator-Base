add_library(registercontrollertest registercontroller.cpp)

add_library(statusregistertest model/statusregister.cpp)

# add_library(registercontroller ../../src/register/registercontroller.cpp)

add_library(register ../../src/register/model/register.cpp)

add_library(statusregister ../../src/register/model/statusregister.cpp)

target_link_libraries(registercontrollertest
    PRIVATE statusregistertest
    #PRIVATE registercontroller
    PRIVATE register
    PRIVATE statusregister
)