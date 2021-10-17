cmake_minimum_required(VERSION 3.20)
project(Deque)

set(CMAKE_CXX_STANDARD 17)

add_executable(Deque main.cpp Deque.h AllocInterface.h Alloc.h)
