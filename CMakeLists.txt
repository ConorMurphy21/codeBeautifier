cmake_minimum_required(VERSION 3.13)
project(codeBeautifier)

set(CMAKE_CXX_STANDARD 14)

find_library(codeBeautifier_lib codeBeautifier)


include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)


add_subdirectory(src)
add_subdirectory(lib/googletest-master)
add_subdirectory(test)
