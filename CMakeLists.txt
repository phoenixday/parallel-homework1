cmake_minimum_required(VERSION 3.0)
project(hw1)

set(CMAKE_CXX_STANDARD 17)

add_executable(hw1 main.cpp PosixQueue.cpp Node.h LockFreeQueue.h LockFreeQueue.cpp)
