cmake_minimum_required(VERSION 3.8)
project(ConcurrentPrime)

set(CMAKE_CXX_STANDARD 11)

#add_definitions(-DPTHREAD)

link_libraries(pthread)
set(SOURCE_FILES main.cpp PrimeComputer.cpp PrimeComputer.h)
add_executable(ConcurrentPrime ${SOURCE_FILES})