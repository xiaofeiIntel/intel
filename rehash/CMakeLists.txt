cmake_minimum_required(VERSION 3.8)
project(rehash)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c rehash.h rehash.c)
add_executable(rehash ${SOURCE_FILES})

find_package(Threads REQUIRED)
target_link_libraries(rehash Threads::Threads)