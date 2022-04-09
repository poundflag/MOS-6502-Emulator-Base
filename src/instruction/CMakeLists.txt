add_library(addressmodeconversion addressmodeconversion.cpp)

add_library(instructiondecoderom instructiondecoderom.cpp)

add_library(instruction instruction.cpp)

target_link_libraries(instruction
    PUBLIC addressmodeconversion
    PUBLIC instructiondecoderom
)
