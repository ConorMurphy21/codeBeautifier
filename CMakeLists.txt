cmake_minimum_required(VERSION 3.13)
project(codeBeautifier)

set(CMAKE_CXX_STANDARD 14)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s -O3")
#set(CMAKE_EXE_LINKER_FLAGS -static)

add_executable(codeBeautifier main.cpp)

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)

target_link_libraries(codeBeautifier src)
