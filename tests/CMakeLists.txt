find_package(Catch2 2.13.8 REQUIRED)

add_executable(tests test.cpp)
add_executable(testGroups test2.cpp)

add_compile_options(--coverage)
add_link_options(--coverage)
target_link_libraries(tests tree DFA mRegex Catch2::Catch2WithMain nfa)
target_link_libraries(testGroups tree DFA mRegex Catch2::Catch2WithMain nfa)
