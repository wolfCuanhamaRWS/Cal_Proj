cmake_minimum_required(VERSION 3.16)
project(Inspect)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)


include_directories(src)
add_executable(Inspect main.cpp Tests/tests.cpp
        )


target_link_libraries(Inspect gtest gtest_main)

