
include_directories(../myRegex)
add_executable(prog main.cpp)
target_link_libraries(prog myRegex)