cmake_minimum_required(VERSION 3.8)
project(atomic11)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c)
add_executable(atomic11 ${SOURCE_FILES})

find_package(Threads REQUIRED)
target_link_libraries(atomic11 Threads::Threads)