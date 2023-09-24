cmake_minimum_required(VERSION 3.10)
project(Classes_in_C++)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# include(FetchContent)

# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
#   DOWNLOAD_EXTRACT_TIMESTAMP true
# )

# FetchContent_MakeAvailable(googletest)

# enable_testing()

add_executable(
    main 
    main.cpp 
    seven_constructors.cpp 
    seven_getters.cpp 
    seven_operators.cpp 
    seven_private.cpp
)
