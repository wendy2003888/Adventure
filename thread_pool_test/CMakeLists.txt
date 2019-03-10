cmake_minimum_required (VERSION 2.6)
project (THREADPOOL)

include_directories("${PROJECT_SOURCE_DIR}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -pthread -O2")


add_executable(threadpool main.cpp threadpool.h)
add_executable(threadpool1y example1y.cpp threadpool1y.h)