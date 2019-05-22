

include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(codeBeautifier_tests testsetup.cpp)

target_link_libraries(codeBeautifier_tests gtest gtest_main)
target_link_libraries(codeBeautifier_tests src)
