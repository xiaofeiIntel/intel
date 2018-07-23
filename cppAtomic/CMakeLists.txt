cmake_minimum_required(VERSION 3.8)
project(cppAtomic)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(cppAtomic ${SOURCE_FILES})

find_package(Threads REQUIRED)
target_link_libraries(cppAtomic Threads::Threads)