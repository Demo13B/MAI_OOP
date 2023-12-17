cmake_minimum_required(VERSION 3.10)
project(Balagurs_Fate_3_Dynamic)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

add_executable(main 
    main.cpp
    npc.cpp
    dragon.cpp
    wandering_knight.cpp
    elf.cpp
)

add_executable(tests
    tests.cpp
    npc.cpp
    dragon.cpp
    wandering_knight.cpp
    elf.cpp
)

include(FetchContent)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)

FetchContent_MakeAvailable(googletest)

enable_testing()

target_link_libraries(tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)