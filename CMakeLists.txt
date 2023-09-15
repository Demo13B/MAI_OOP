cmake_minimum_required(VERSION 3.10)
project(First_Prog_on_C++)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(googletest)

add_executable(tests tests.cpp crazyChecker.cpp)
add_executable(main main.cpp crazyChecker.cpp)
target_link_libraries(tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
