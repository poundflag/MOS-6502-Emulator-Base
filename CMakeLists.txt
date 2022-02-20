####################################
# root
####################################

cmake_minimum_required(VERSION 3.5.0)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

project(TestProject)

add_subdirectory(test)
add_subdirectory(src)
