cmake_minimum_required(VERSION 3.22.1)
project(test)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(my)
add_subdirectory(myRegex)
include_directories(myRegex )
add_subdirectory(tests)