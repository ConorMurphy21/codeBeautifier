
cmake_minimum_required(VERSION 3.13)
project(CodeBeautifier VERSION 1.0)


set(CMAKE_CXX_STANDARD 14)

set(DISABLE_TEST)

#These settings are my current jenky way of deploying my project, but with these settings enabled,
#the debugger does not work

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s -O3")
set(CMAKE_EXE_LINKER_FLAGS -static)

add_executable(bfy main.cpp)

include_directories(src)

add_subdirectory(src)
add_subdirectory(test EXCLUDE_FROM_ALL)
add_subdirectory(testExecutables EXCLUDE_FROM_ALL)

install(TARGETS bfy)

target_link_libraries(bfy src)

#pack variables


set(CPACK_NSIS_MODIFY_PATH "ON")

include(CPack)



