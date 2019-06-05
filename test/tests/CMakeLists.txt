

include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(codeBeautifier_tests ArrObjBasicTest.cpp CodeObjBasicTest.cpp TextObjBasicTest.cpp ArrObjBasicTest.h ArrObjCreateTest.cpp ArgumentFactoryTest.cpp TernaryTrieTest.cpp TextObjUniquifyTest.cpp TextObjParamTest.h TextObjCondenseTest.cpp CodeObjExpandCondenseTest.cpp)

target_link_libraries(codeBeautifier_tests gtest gtest_main)
target_link_libraries(codeBeautifier_tests src)
