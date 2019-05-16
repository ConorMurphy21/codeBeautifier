include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(tests testsetup.cpp ${SOURCE_FILES})

target_link_libraries(tests gtest gtest_main)
