cmake_minimum_required(VERSION 3.8)
project(multifun_thread)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c subThreadFun.c subThreadFun.h)
add_executable(multifun_thread ${SOURCE_FILES})

find_package(Threads REQUIRED)
target_link_libraries(multifun_thread Threads::Threads)