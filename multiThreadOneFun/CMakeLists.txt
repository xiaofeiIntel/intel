cmake_minimum_required(VERSION 3.8)
project(multiThreadOneFun)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(multiThreadOneFun ${SOURCE_FILES})

find_package(Threads REQUIRED)
target_link_libraries(multiThreadOneFun Threads::Threads)