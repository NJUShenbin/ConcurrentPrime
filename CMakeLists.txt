cmake_minimum_required(VERSION 3.8)
project(ConcurrentPrime)

set(CMAKE_CXX_STANDARD 11)

#add_definitions(-DPTHREAD)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

link_libraries(pthread)
set(SOURCE_FILES main.cpp PrimeComputer.cpp PrimeComputer.h)
add_executable(ConcurrentPrime ${SOURCE_FILES})