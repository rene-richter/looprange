cmake_minimum_required(VERSION 3.0)
# used on Debian Jessie (Udoo) 
# run cmake .. twice ?!
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Debug)

project (Loop)
add_executable(loopdemo loop.demo.cpp)
add_executable(looptest range.test.cpp generate.test.cpp linspace.test.cpp)

add_executable(perf_linspace benchmark/linspace.cpp)
add_executable(perf_simple benchmark/simpletiming.cpp)
add_executable(wrong doc/wrongway.cpp)

enable_testing()
add_test(loopTest looptest)
