cmake_minimum_required(VERSION 3.0)
# used on Debian Jessie (Udoo) 
# run cmake .. twice ?!
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Debug)

project (Loop)
add_executable(loopdemo loop.demo.cpp)
add_executable(looptest main.test.cpp range.test.cpp generate.test.cpp linspace.test.cpp)

# add_executable(benchmark benchmark/bm_loop.cpp)
# add_executable(wrong doc/wrongway.cpp)

enable_testing()
add_test(loopTest looptest)
