cmake_minimum_required(VERSION 3.10)
project(Inherited_classes)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    main 
    main.cpp
    pentagon.cpp
    hexagon.cpp
    octagon.cpp
    array.cpp
)

add_executable(
    tests
    tests.cpp
    pentagon.cpp
    hexagon.cpp
    octagon.cpp
    array.cpp
)

target_link_libraries(tests GTest::gtest_main)


include(GoogleTest)
gtest_discover_tests(tests)
