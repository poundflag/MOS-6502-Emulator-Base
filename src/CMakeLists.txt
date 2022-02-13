add_executable(main main.cpp)

add_subdirectory(
    register/ registercontroller
)

add_subdirectory(
    bus/ buscontroller
)

# Make sure you link your targets with this command. It can also link libraries and
# even flags, so linking a target that does not exist will not give a configure-time error.
target_link_libraries(
    main 
    PRIVATE registercontroller 
    PRIVATE buscontroller
)

