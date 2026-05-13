
cmake_minimum_required(VERSION 3.14)
project(v2.0)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(main main.cpp Studentas.cpp Funkcijos.cpp Zmones.cpp)

add_executable(testai Test.cpp Studentas.cpp Funkcijos.cpp)

target_link_libraries(testai
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(testai)