

include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

#will fix the cmake structure later
add_executable(codeBeautifier_tests arrObjTests/ArrObjBasicTest.cpp codeObjTests/CodeObjBasicTest.cpp
        textObjTests/TextObjBasicTest.cpp arrObjTests/ArrObjBasicTest.h arrObjTests/ArrObjCreateTest.cpp
        argumentTests/ArgumentFactoryTest.cpp ternaryTrieTests/TernaryTrieTest.cpp
        textObjTests/TextObjUniquifyTest.cpp textObjTests/TextObjParamTest.h
        textObjTests/TextObjCondenseTest.cpp codeObjTests/CodeObjExpandCondenseTest.cpp
        codeObjTests/CodeObjExpandTest.cpp)

target_link_libraries(codeBeautifier_tests gtest gtest_main)
target_link_libraries(codeBeautifier_tests src)
